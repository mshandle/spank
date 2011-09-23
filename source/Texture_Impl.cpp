/*!
 * \file Texture_Impl.cpp
 * \date 7-22-2011 10:49:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Texture_Impl.h"
#include <util/IFileUtil.h>
#include <util/IDebugUtil.h>
#include <msg/MsgCommon.h>
#include <msg/MsgID.h>
#include <GLES2/gl2.h>

Texture_Impl::Texture_Impl(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample)
{
	m_nTextureWidth = 0;
	m_nTextureHeight = 0;
	m_nGLTextureID = 0;

	m_bOK = LoadTextureFromFile(pszFileName, eSample);
}

Texture_Impl::Texture_Impl(const void* pPixelData, int nWidth, int nHeight, TEXTURE_SAMPLE_TYPE eSample)
{
	m_nTextureWidth = 0;
	m_nTextureHeight = 0;
	m_nGLTextureID = 0;

	m_bOK = LoadTextureFromMemory(pPixelData, nWidth, nHeight, eSample);
}

Texture_Impl::~Texture_Impl()
{
	MsgCommon msgCommon(MI_TEXTURE_DESTROIED);
	msgCommon.SetObject(this);
	CallEvent(msgCommon);
	FreeGLTexture();
}

int Texture_Impl::GetWidth() const
{
	return m_nTextureWidth;
}

int Texture_Impl::GetHeight() const
{
	return m_nTextureHeight;
}

GLuint Texture_Impl::GetGLTextureID() const
{
	return m_nGLTextureID;
}

bool Texture_Impl::LoadTextureFromFile(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample)
{
	Image* pImage = new Image(pszFileName);
	if (!pImage || !pImage->IsOK())
	{
		SAFE_DELETE(pImage);
		return false;
	}

	// create gl texture
	bool bOK = CreateGLTexture(pImage, eSample);

	// free image data
	SAFE_DELETE(pImage);

	return bOK;
}

bool Texture_Impl::LoadTextureFromMemory(const void* pPixelData, int nWidth, int nHeight, TEXTURE_SAMPLE_TYPE eSample)
{
	FreeGLTexture();

	glGenTextures(1, &m_nGLTextureID);
	if (m_nGLTextureID == 0) return false;

	m_nTextureWidth = nWidth;
	m_nTextureHeight = nHeight;

	if (!IsValidTextureSize(m_nTextureWidth) || !IsValidTextureSize(m_nTextureHeight))
	{
		LOGE("invalid texture size: %dx%d", m_nTextureWidth, m_nTextureHeight);
	}

	glBindTexture(GL_TEXTURE_2D, m_nGLTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nTextureWidth, m_nTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pPixelData);

	if (eSample == TST_POINT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	return true;
}

bool Texture_Impl::CreateGLTexture(Image* pImage, TEXTURE_SAMPLE_TYPE eSample)
{
	FreeGLTexture();

	glGenTextures(1, &m_nGLTextureID);
	if (m_nGLTextureID == 0) return false;

	m_nTextureWidth = pImage->GetWidth();
	m_nTextureHeight = pImage->GetHeight();

	if (!IsValidTextureSize(m_nTextureWidth) || !IsValidTextureSize(m_nTextureHeight))
	{
		LOGE("invalid texture size: %dx%d", m_nTextureWidth, m_nTextureHeight);
	}

	glBindTexture(GL_TEXTURE_2D, m_nGLTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_nTextureWidth, m_nTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pImage->GetPixelData());

	if (eSample == TST_POINT)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	}

	return true;
}

void Texture_Impl::FreeGLTexture()
{
	if (m_nGLTextureID != 0)
	{
		glDeleteTextures(1, &m_nGLTextureID);
		m_nGLTextureID = 0;
	}
}

bool Texture_Impl::IsValidTextureSize(uint nSize)
{
	static const uint s_nValidSize[] = {16, 32, 64, 128, 256, 512, 1024, 2048, 0};

	bool bValid = false;

	int nIndex = 0;
	while (s_nValidSize[nIndex] != 0)
	{
		if (nSize == s_nValidSize[nIndex])
		{
			bValid = true;
			break;
		}
		++nIndex;
	}

	return bValid;
}
