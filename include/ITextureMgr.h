/*!
 * \file ITextureMgr.h
 * \date 7-22-2011 10:45:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ITEXTUREMGR_H__
#define __ITEXTUREMGR_H__

#include "ISingleton.h"
#include "ITexture.h"

class ITextureMgr : public ISingleton
{
public:
	DECLARE_RTTI(ITextureMgr, ISingleton);

	static ITextureMgr& GetInstance();

	
	/*!
	 * \brief create texture from file, (if the texture exist, increase the texture reference and return the
	 * exist one.
	 * \param pszFileName file name of the texture
	 * \param eSample texture sample type /see TEXTURE_SAMPLE_TYPE
	 * \return if success return a pointer to the texture, otherwise return NULL
	 */
	virtual ITexture* CreateTexture(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample = TST_POINT) = 0;
	
	/*!
	 * \brief create texture from memory, use it with caution
	 * \param pPixelData texture pixel data in RGBA format
	 * \param nWidth texture width
	 * \param nHeight texture height
	 * \param eSample texture sample type /see TEXTURE_SAMPLE_TYPE
	 * \return if success return a pointer to the texture, otherwise return NULL
	 */
	virtual ITexture* CreateTextureFromMemory(const void* pPixelData, int nWidth, int nHeight, TEXTURE_SAMPLE_TYPE eSample = TST_POINT) = 0;
};

#endif // __ITEXTUREMGR_H__
