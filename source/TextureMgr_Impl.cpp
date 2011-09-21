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
	// TODO: 
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
	if (!pTexture) return false;

	for (TM_TEXTURE::iterator it = m_TextureMap.begin(); it != m_TextureMap.end(); ++it)
	{
		if (it->second == pTexture)
		{
			m_TextureMap.erase(it);
			return true;
		}
	}

	return false;
}
