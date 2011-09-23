/*!
 * \file Texture_Impl.h
 * \date 7-22-2011 10:48:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __TEXTURE_IMPL_H__
#define __TEXTURE_IMPL_H__

#include <ITexture.h>
#include <Image.h>
#include <GLES2/gl2.h>

class Texture_Impl : public ITexture
{
public:
	DECLARE_RTTI(Texture_Impl, ITexture);

	Texture_Impl(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample);
	Texture_Impl(const void* pPixelData, int nWidth, int nHeight, TEXTURE_SAMPLE_TYPE eSample);
	virtual ~Texture_Impl();

	virtual int GetWidth() const;
	virtual int GetHeight() const;

	GLuint GetGLTextureID() const;

private:
	bool LoadTextureFromFile(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample);
	bool LoadTextureFromMemory(const void* pPixelData, int nWidth, int nHeight, TEXTURE_SAMPLE_TYPE eSample);

	bool CreateGLTexture(Image* pImage, TEXTURE_SAMPLE_TYPE eSample);
	void FreeGLTexture();

	bool IsValidTextureSize(uint nSize);

private:
	int m_nTextureWidth;
	int m_nTextureHeight;
	GLuint m_nGLTextureID;

};
#endif // __TEXTURE_IMPL_H__
