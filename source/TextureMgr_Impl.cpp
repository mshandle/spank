/*!
 * \file TextureMgr_Impl.cpp
 * \date 7-25-2011 10:19:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "TextureMgr_Impl.h"
#include "Texture_Impl.h"
#include <msg/MsgID.h>
#include <msg/MsgCommon.h>
#include <util/IDebugUtil.h>

ITextureMgr& ITextureMgr::GetInstance()
{
	static TextureMgr_Impl s_TextureMgr_Impl;
	return s_TextureMgr_Impl;
}

TextureMgr_Impl::TextureMgr_Impl()
{
	// TODO: 
}

TextureMgr_Impl::~TextureMgr_Impl()
{
	// TODO: 
}

bool TextureMgr_Impl::Initialize()
{
	return true;
}

void TextureMgr_Impl::Terminate()
{
	// check m_TextureMap and m_MemoryTextureSet exist textures
	for (TM_TEXTURE::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); ++it)
	{
		ITexture* pTexture = it->second;
		LOGE("un-released texture: %s, ref: %d", it->first.c_str(), pTexture->GetRef());
		pTexture->SetRef(0);
		SAFE_RELEASE(pTexture);
	}
	m_TextureMap.clear();

	for (TS_TEXTURE::iterator it = m_MemoryTextureSet.begin(); it != m_MemoryTextureSet.end(); ++it)
	{
		ITexture* pTexture = (*it);
		LOGE("un-released memory texture: %x, ref: %d", pTexture, pTexture->GetRef());
		pTexture->SetRef(0);
		SAFE_RELEASE(pTexture);
	}
	m_MemoryTextureSet.clear();
}

ITexture* TextureMgr_Impl::CreateTexture(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample /* = TST_POINT */)
{
	ITexture* pTexture = FindTexture(pszFileName);
	if (pTexture)
	{
		pTexture->IncRef();
		return pTexture;
	}

	Texture_Impl* pTexture_Impl = new Texture_Impl(pszFileName, eSample);
	if (!pTexture_Impl || !pTexture_Impl->IsOK())
	{
		SAFE_DELETE(pTexture_Impl);
		return NULL;
	}

	// connect the destroy event
	pTexture_Impl->ConnectEvent(MI_TEXTURE_DESTROIED, this, (MSG_CALLBACK)&TextureMgr_Impl::OnTextureDestroied);
	// cache the texture
	m_TextureMap.insert(std::make_pair(pszFileName, pTexture_Impl));

	return pTexture_Impl;
}

ITexture* TextureMgr_Impl::CreateTextureFromMemory(const void* pPixelData, int nWidth, int nHeight, TEXTURE_SAMPLE_TYPE eSample /*= TST_POINT*/)
{
	Texture_Impl* pTexture_Impl = new Texture_Impl(pPixelData, nWidth, nHeight, eSample);
	if (!pTexture_Impl || !pTexture_Impl->IsOK())
	{
		SAFE_DELETE(pTexture_Impl);
		return NULL;
	}

	// connect the destroy event
	pTexture_Impl->ConnectEvent(MI_TEXTURE_DESTROIED, this, (MSG_CALLBACK)&TextureMgr_Impl::OnMemoryTextureDestroied);
	// cache the texture
	m_MemoryTextureSet.insert(pTexture_Impl);

	return pTexture_Impl;
}

ITexture* TextureMgr_Impl::FindTexture(const char* pszFileName)
{
	TM_TEXTURE::iterator itfound = m_TextureMap.find(pszFileName);
	if (itfound == m_TextureMap.end()) return NULL;

	return itfound->second;
}

bool TextureMgr_Impl::OnTextureDestroied(IMsgBase* pMsg)
{
	MsgCommon* pMsgCommon = (MsgCommon*)pMsg;
	ITexture* pTexture = (ITexture*)pMsgCommon->GetObject();
	if (!pTexture) return true;

	for (TM_TEXTURE::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); ++it)
	{
		if (it->second == pTexture)
		{
			m_TextureMap.erase(it);
			return true;
		}
	}

	LOGE("free texture error, un-cached texture");
	return true;
}

bool TextureMgr_Impl::OnMemoryTextureDestroied(IMsgBase* pMsg)
{
	MsgCommon* pMsgCommon = (MsgCommon*)pMsg;
	ITexture* pTexture = (ITexture*)pMsgCommon->GetObject();
	if (!pTexture) return true;

	TS_TEXTURE::iterator itfound = m_MemoryTextureSet.find(pTexture);
	if (itfound == m_MemoryTextureSet.end())
	{
		LOGE("free memory texture error, un-cached memory texture");
		return true;
	}

	m_MemoryTextureSet.erase(itfound);
	return true;
}
