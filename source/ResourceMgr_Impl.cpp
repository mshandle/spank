/*!
 * \file ResourceMgr_Impl.cpp
 * \date 12-09-2011 17:07:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ResourceMgr_Impl.h"
#include <ITextureMgr.h>
#include <util/IFileUtil.h>
#include <util/StringUtil.h>
#include <tinyxml-2.6.2/tinyxml.h>

IResourceMgr& IResourceMgr::GetInstance()
{
	static ResourceMgr_Impl s_ResourceMgr_Impl;
	return s_ResourceMgr_Impl;
}

ResourceMgr_Impl::ResourceMgr_Impl()
{
	// TODO: 
}

ResourceMgr_Impl::~ResourceMgr_Impl()
{
	// TODO: 
}

bool ResourceMgr_Impl::Initialize()
{
	// TODO: 
	return true;
}

void ResourceMgr_Impl::Terminate()
{
	for (TV_TEXTURE::iterator it = m_vTextures.begin(); it != m_vTextures.end(); ++it)
	{
		ITexture* pTexture = (*it);
		SAFE_RELEASE(pTexture);
	}
	m_vTextures.clear();
}

bool ResourceMgr_Impl::AddImagePieceList(const char* pszFile)
{
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszFile);
	if (!pReader) return false;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);

	if (doc.Error()) return false;

	TiXmlElement* pElmImagePiece = doc.RootElement();
	if (!pElmImagePiece || strcmp(pElmImagePiece->Value(), "ImagePiece") != 0) return false;

	TiXmlElement* pElmImageList = pElmImagePiece->FirstChildElement("ImageList");
	if (!pElmImageList) return false;

	// parse texture list
	TM_TEXTURE_INFO textureInfoMap;
	TiXmlElement* pElmImage = pElmImageList->FirstChildElement("Image");
	while (pElmImage)
	{
		int nID = 0;
		if (!pElmImage->Attribute("id", &nID)) return false;

		const char* pszTexture = pElmImage->Attribute("file");
		if (!pszTexture) return false;

		TEXTURE_SAMPLE_TYPE eSampleType = TST_POINT;
		const char* pszSample = pElmImage->Attribute("sample");
		if (StringUtil::IsEqual(pszSample, "linear")) eSampleType = TST_LINEAR;

		ITexture* pTexture = ITextureMgr::GetInstance().CreateTexture(pszTexture, eSampleType);
		if (!pTexture) return false;

		textureInfoMap.insert(std::make_pair(nID, pTexture));
		m_vTextures.push_back(pTexture);

		pElmImage = pElmImage->NextSiblingElement("Image");
	}

	TiXmlElement* pElmPieceList = pElmImagePiece->FirstChildElement("PieceList");
	// parse piece list
	TiXmlElement* pElmPiece = pElmPieceList->FirstChildElement("Piece");
	while (pElmPiece)
	{
		const char* pszName = pElmPiece->Attribute("id");
		if (!pszName) return false;

		int nTextureID = 0;
		if (!pElmPiece->Attribute("image", &nTextureID)) return false;

		ITexture* pTexture = FindTexture(textureInfoMap, nTextureID);
		if (!pTexture) return false;

		int x = 0, y = 0, width = 0, height = 0;
		if (!pElmPiece->Attribute("x", &x)) return false;
		if (!pElmPiece->Attribute("y", &y)) return false;
		if (!pElmPiece->Attribute("width", &width)) return false;
		if (!pElmPiece->Attribute("height", &height)) return false;

		float fTextureWidth = (float)pTexture->GetWidth();
		float fTextureHeight = (float)pTexture->GetHeight();

		IMAGE_PIECE pieceInfo;
		pieceInfo.width = (float)width;
		pieceInfo.height = (float)height;
		pieceInfo.u = (x)/fTextureWidth;
		pieceInfo.v = (fTextureHeight-y-height)/fTextureHeight;		// invert the y-axis for opengl
		pieceInfo.du = (width)/fTextureWidth;
		pieceInfo.dv = (height)/fTextureHeight;
		pieceInfo.pTexture = pTexture;

		// TODO: check piece name existing ?
		m_TexturePieceMap.insert(std::make_pair(pszName, pieceInfo));

		pElmPiece = pElmPiece->NextSiblingElement("Piece");
	}

	return true;
}

const IMAGE_PIECE* ResourceMgr_Impl::FindImagePiece(const char* pszName)
{
	TM_IMAGE_PIECE::iterator itfound = m_TexturePieceMap.find(pszName);
	if (itfound == m_TexturePieceMap.end()) return NULL;

	return &(itfound->second);
}

ITexture* ResourceMgr_Impl::FindTexture(TM_TEXTURE_INFO textureInfoMap, int nID)
{
	TM_TEXTURE_INFO::iterator itfound = textureInfoMap.find(nID);
	if (itfound == textureInfoMap.end()) return NULL;

	return itfound->second;
}
