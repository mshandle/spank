/*!
 * \file Shader_Impl.h
 * \date 7-25-2011 10:14:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SHADER_IMPL_H__
#define __SHADER_IMPL_H__

#include <IShader.h>
#include <StreamReader.h>
#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>
#include <string>
#include <map>

class Shader_Impl : public IShader
{
public:
	typedef struct TEXTURE_COMMIT_INFO_tag
	{
		ITexture* pTexture;
		uint nIndex;
	} TEXTURE_COMMIT_INFO;

	typedef std::map<std::string, Matrix4x4> TM_MATRIX_COMMIT_INFO;
	typedef std::map<std::string, Vector4> TM_VECTOR_COMMIT_INFO;
	typedef std::map<std::string, TEXTURE_COMMIT_INFO> TM_TEXTURE_COMMIT_INFO;

public:
	DECLARE_RTTI(Shader_Impl, IShader);

	Shader_Impl(StreamReader* pVertexShader, StreamReader* pFregmentShader, VertexAttribute* pVertexAttribute);
	virtual ~Shader_Impl();

	virtual bool SetMatrix4x4(const char* pszParamName, const Matrix4x4& m);
	virtual bool SetVector4(const char* pszParamName, const Vector4& v);
	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture, uint nIndex = 0);

	virtual const VertexAttribute* GetVertexAttribute() const;
	virtual void Reset();
	virtual bool Commit(const void* pVerts);

private:
	bool CreateProgram(StreamReader* pVertexShader, StreamReader* pFregmentShader, VertexAttribute* pVertexAttribute);
	void FreeProgram();

	GLuint CreateShader(const char* pszShaderSource, GLenum eType);
	void FreeShader(GLuint nShader);

	void FlushCommitInfo();

	GLenum GetGLType(ATTRIBUTE_ITEM_TYPE eType);

private:
	VertexAttribute* m_pVertexAttribute;
	GLuint m_glProgramObject;

	TM_MATRIX_COMMIT_INFO m_mapCommitMatrix;
	TM_VECTOR_COMMIT_INFO m_mapCommitVector;
	TM_TEXTURE_COMMIT_INFO m_mapCommitTexture;

};
#endif // __SHADER_IMPL_H__
