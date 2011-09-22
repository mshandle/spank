/*!
 * \file Shader_Impl.cpp
 * \date 7-25-2011 10:15:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Shader_Impl.h"
#include "Texture_Impl.h"
#include <util/IDebugUtil.h>
#include <msg/MsgCommon.h>
#include <msg/MsgID.h>
#include <IShaderMgr.h>

Shader_Impl::Shader_Impl(StreamReader* pVertexShader, StreamReader* pFregmentShader, VertexAttribute* pVertexAttribute)
{
	m_pVertexAttribute = NULL;
	m_glProgramObject = 0;

	m_bOK = CreateProgram(pVertexShader, pFregmentShader, pVertexAttribute);
}

Shader_Impl::~Shader_Impl()
{
	MsgCommon msgCommon(MI_SHADER_DESTROIED);
	msgCommon.SetObject(this);
	CallEvent(msgCommon);
	FreeProgram();
}

bool Shader_Impl::SetMatrix4x4(const char* pszParamName, const Matrix4x4& m)
{
	if (!pszParamName) return false;

	m_mapCommitMatrix.insert(std::make_pair(pszParamName, m));
	return true;
}

bool Shader_Impl::SetVector4(const char* pszParamName, const Vector4& v)
{
	if (!pszParamName) return false;

	m_mapCommitVector.insert(std::make_pair(pszParamName, v));
	return true;
}

bool Shader_Impl::SetTexture(const char* pszParamName, ITexture* pTexture, uint nIndex /* = 0 */)
{
	if (!pszParamName || !pTexture) return false;

	TEXTURE_COMMIT_INFO info;
	info.pTexture = pTexture;
	info.nIndex = nIndex;
	m_mapCommitTexture.insert(std::make_pair(pszParamName, info));
	return true;
}

void Shader_Impl::Reset()
{
	m_mapCommitMatrix.clear();
	m_mapCommitVector.clear();
	m_mapCommitTexture.clear();
}

const VertexAttribute* Shader_Impl::GetVertexAttribute() const
{
	return m_pVertexAttribute;
}

bool Shader_Impl::Commit(const void* pVerts)
{
	glUseProgram(m_glProgramObject);
	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glUseProgram error code: 0x%04x", eError);

	FlushCommitInfo();

	if (pVerts == NULL) return false;

	// setup vertex attributes
	int nNumAttrs = m_pVertexAttribute->GetNumAttributeItems();
	for (int i = 0; i < nNumAttrs; ++i)
	{
		const ATTRIBUTE_ITEM* pAttrItem = m_pVertexAttribute->GetAttributeItem(i);

		glEnableVertexAttribArray(i);
		eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glEnableVertexAttribArray error code: 0x%04x", eError);

		GLenum eType = GetGLType(pAttrItem->eItemType);
		glVertexAttribPointer(i, pAttrItem->nSize, eType, GL_FALSE, m_pVertexAttribute->GetStride(), ((const uchar*)pVerts)+pAttrItem->nOffset);
		eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glVertexAttribPointer error code: 0x%04x", eError);

		glBindAttribLocation(m_glProgramObject, i, pAttrItem->szParamName);
		eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glBindAttribLocation error code: 0x%04x", eError);
	}

	return true;
}

bool Shader_Impl::CreateProgram(StreamReader* pVertexShader, StreamReader* pFregmentShader, VertexAttribute* pVertexAttribute)
{
	if (!pVertexAttribute) return false;

	GLuint glVertexShader = CreateShader((const char*)pVertexShader->GetBuffer(), GL_VERTEX_SHADER);
	if (glVertexShader == 0)
	{
		LOGE("create vertex shader failed");
		return false;
	}

	GLuint glFragmentShader = CreateShader((const char*)pFregmentShader->GetBuffer(), GL_FRAGMENT_SHADER);
	if (glFragmentShader == 0)
	{
		FreeShader(glVertexShader);
		LOGE("create fregment shader failed");
		return false;
	}

	m_glProgramObject = glCreateProgram();
	if (m_glProgramObject == 0)
	{
		FreeShader(glVertexShader);
		FreeShader(glFragmentShader);
		LOGE("create shader program failed");
		return false;
	}

	glAttachShader(m_glProgramObject, glVertexShader);
	glAttachShader(m_glProgramObject, glFragmentShader);
	glLinkProgram(m_glProgramObject);

	FreeShader(glVertexShader);
	FreeShader(glFragmentShader);

	GLint glLinked = 0;
	glGetProgramiv(m_glProgramObject, GL_LINK_STATUS, &glLinked);
	if (glLinked != GL_TRUE)
	{
		GLint nErrorLength = 0;
		glGetProgramiv(m_glProgramObject, GL_INFO_LOG_LENGTH, &nErrorLength);
		if (nErrorLength > 0)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetProgramInfoLog(m_glProgramObject, nErrorLength, NULL, pszErrorLog);
			LOGE("error linking program: %s", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteProgram(m_glProgramObject);
		return false;
	}

	m_pVertexAttribute = pVertexAttribute;
	return true;
}

void Shader_Impl::FreeProgram()
{
	if (m_glProgramObject)
	{
		glDeleteProgram(m_glProgramObject);
		m_glProgramObject = 0;
	}

	SAFE_RELEASE(m_pVertexAttribute);
}

GLuint Shader_Impl::CreateShader(const char* pszShaderSource, GLenum eType)
{
	GLuint glShader = glCreateShader(eType);
	if (glShader == 0) return 0;

	glShaderSource(glShader, 1, &pszShaderSource, NULL);
	glCompileShader(glShader);

	// check the compile status
	GLint glCompiled = 0;
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &glCompiled);
	if (glCompiled != GL_TRUE)
	{
		GLint nErrorLength = 0;
		glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &nErrorLength);
		if (nErrorLength > 0)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetShaderInfoLog(glShader, nErrorLength, NULL, pszErrorLog);
			LOGE("error compiling shader: %s", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteShader(glShader);
		return 0;
	}

	return glShader;
}

void Shader_Impl::FreeShader(GLuint nShader)
{
	glDeleteShader(nShader);
}

void Shader_Impl::FlushCommitInfo()
{
	for (TM_MATRIX_COMMIT_INFO::iterator it = m_mapCommitMatrix.begin(); it != m_mapCommitMatrix.end(); ++it)
	{
		int location = glGetUniformLocation(m_glProgramObject, it->first.c_str());
		if (location == -1)
		{
			LOGE("glGetUniformLocation %s failed", it->first.c_str());
			continue;
		}

		const Matrix4x4& m = it->second;
		glUniformMatrix4fv(location, 1, GL_FALSE, m.e);
		GLenum eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glUniformMatrix4fv error code: 0x%04x", eError);
	}
	m_mapCommitMatrix.clear();

	for (TM_VECTOR_COMMIT_INFO::iterator it = m_mapCommitVector.begin(); it != m_mapCommitVector.end(); ++it)
	{
		int location = glGetUniformLocation(m_glProgramObject, it->first.c_str());
		if (location == -1)
		{
			LOGE("glGetUniformLocation %s failed", it->first.c_str());
			continue;
		}

		const Vector4& v = it->second;
		glUniform4f(location, v.x, v.y, v.z, v.w);
		GLenum eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glUniform4f error code: 0x%04x", eError);
	}
	m_mapCommitVector.clear();

	for (TM_TEXTURE_COMMIT_INFO::iterator it = m_mapCommitTexture.begin(); it != m_mapCommitTexture.end(); ++it)
	{
		int location = glGetUniformLocation(m_glProgramObject, it->first.c_str());
		if (location == -1)
		{
			LOGE("glGetUniformLocation %s failed", it->first.c_str());
			continue;
		}

		Texture_Impl* pTexture_Impl = (Texture_Impl*)it->second.pTexture;
		glActiveTexture(GL_TEXTURE0+it->second.nIndex);
		GLenum eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glActiveTexture error code: 0x%04x", eError);

		glBindTexture(GL_TEXTURE_2D, pTexture_Impl->GetGLTextureID());
		eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glBindTexture error code: 0x%04x", eError);

		glUniform1i(location, it->second.nIndex);
		eError = glGetError();
		if (eError != GL_NO_ERROR) LOGE("glUniform1i error code: 0x%04x", eError);
	}
	m_mapCommitTexture.clear();
}

GLenum Shader_Impl::GetGLType(ATTRIBUTE_ITEM_TYPE eType)
{
	static const GLenum s_GLType[NUM_AIT] = 
	{
		GL_FLOAT,			// AT_UNKNOWN,
		GL_BYTE,			// AT_BYTE,
		GL_UNSIGNED_BYTE,	// AT_UNSIGNED_BYTE,
		GL_SHORT,			// AT_SHORT,
		GL_UNSIGNED_SHORT,	// AT_UNSIGNED_SHORT,
		GL_FLOAT,			// AT_FLOAT,
		GL_FIXED,			// AT_FIXED,
		GL_HALF_FLOAT_OES,	// AT_HALF_FLOAT_OES,
	};

	if (eType < AIT_UNKNOWN || eType >= NUM_AIT) return GL_FLOAT;
	return s_GLType[eType];
}
