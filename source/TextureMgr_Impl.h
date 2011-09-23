/*!
 * \file TextureMgr_Impl.h
 * \date 7-25-2011 10:17:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __TEXTUREMGR_IMPL_H__
#define __TEXTUREMGR_IMPL_H__

#include <ITextureMgr.h>
#include <msg/IMsgBase.h>
#include <string>
#include <map>
#include <set>

class TextureMgr_Impl : public ITextureMgr
{
public:
	typedef std::map<std::string, ITexture*> TM_TEXTURE;
	typedef std::set<ITexture*> TS_TEXTURE;

public:
	DECLARE_RTTI(TextureMgr_Impl, ITextureMgr);

	TextureMgr_Impl();
	virtual ~TextureMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual ITexture* CreateTexture(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample = TST_POINT);
	virtual ITexture* CreateTextureFromMemory(const void* pPixelData, int nWidth, int nHeight, TEXTURE_SAMPLE_TYPE eSample = TST_POINT);

private:
	ITexture* FindTexture(const char* pszFileName);
	bool OnTextureDestroied(IMsgBase* pMsg);
	bool OnMemoryTextureDestroied(IMsgBase* pMsg);

private:
	TM_TEXTURE m_TextureMap;
	TS_TEXTURE m_MemoryTextureSet;

};
#endif // __TEXTUREMGR_IMPL_H__
