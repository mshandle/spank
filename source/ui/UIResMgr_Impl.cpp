/*!
 * \file FontMgr_Impl.cpp
 * \date 8-22-2011 15:34:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIResMgr_Impl.h"
#include "BitmapFont_Impl.h"
#include <msg/MsgID.h>
#include <msg/MsgCommon.h>
#include <IResourceMgr.h>
#include <util/StringUtil.h>
#include <util/IDebugUtil.h>
#include <util/IFileUtil.h>

IUIResMgr& IUIResMgr::GetInstance()
{
	static UIResMgr_Impl s_UIResMgr_Impl;
	return s_UIResMgr_Impl;
}

UIResMgr_Impl::UIResMgr_Impl()
{
	m_pDefaultFont = NULL;
	StringUtil::ZeroMemory(m_pButtonStyle, sizeof(m_pButtonStyle));
	StringUtil::ZeroMemory(m_pCheckButtonStyle, sizeof(m_pCheckButtonStyle));
	StringUtil::ZeroMemory(m_pRadioButtonStyle, sizeof(m_pRadioButtonStyle));
	m_pDefaultFrame = NULL;
	StringUtil::ZeroMemory(m_pSliderBarStyle, sizeof(m_pSliderBarStyle));
}

UIResMgr_Impl::~UIResMgr_Impl()
{
	// TODO: 
}

bool UIResMgr_Impl::Initialize()
{
	m_pDefaultFont = CreateFont("40px_arial_black.fnt");
	if (!m_pDefaultFont) return false;

	if (!IResourceMgr::GetInstance().AddImagePieceList("ui_default.xml")) return false;
	if (!AddImageFrame("ui_default_frame.xml")) return false;

	m_pDefaultFrame = FindImageFrame("ui_frame_default");
	if (!m_pDefaultFrame) return false;

	if (!InitDefaultButtonStyle()) return false;
	if (!InitDefaultCheckButtonStyle()) return false;
	if (!InitDefaultRadioButtonStyle()) return false;
	if (!InitDefaultSliderBarStyle()) return false;
	return true;
}

void UIResMgr_Impl::Terminate()
{
	SAFE_RELEASE(m_pDefaultFont);
}

IFont* UIResMgr_Impl::CreateFont(const char* pszFontFile)
{
	IFont* pFont = FindFont(pszFontFile);
	if (pFont)
	{
		pFont->IncRef();
		return pFont;
	}

	BitmapFont_Impl* pFont_Impl = new BitmapFont_Impl(pszFontFile);
	if (!pFont_Impl || !pFont_Impl->IsOK())
	{
		SAFE_DELETE(pFont_Impl);
		return NULL;
	}

	// connect the destroy event
	pFont_Impl->ConnectEvent(MI_FONT_DESTROIED, this, (MSG_CALLBACK)&UIResMgr_Impl::OnFontDestroied);
	// cache the texture
	m_mapFont.insert(std::make_pair(pszFontFile, pFont_Impl));

	return pFont_Impl;
}

IFont* UIResMgr_Impl::GetDefaultFont()
{
	return m_pDefaultFont;
}

bool UIResMgr_Impl::AddImageFrame(const char* pszFrameFile)
{
	static const char* s_FramePieces[IFB_NUM] =
	{
		"PieceTopLeft",
		"PieceTopCenter",
		"PieceTopRight",
		"PieceMiddleLeft",
		"PieceMiddleCenter",
		"PieceMiddleRight",
		"PieceBottomLeft",
		"PieceBottomCenter",
		"PieceBottomRight",
	};

	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszFrameFile);
	if (!pReader) return false;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);

	if (doc.Error()) return false;

	TiXmlElement* pElmFrameList = doc.RootElement();
	if (!pElmFrameList || strcmp(pElmFrameList->Value(), "FrameList") != 0) return false;

	TiXmlElement* pElmFrame = pElmFrameList->FirstChildElement("Frame");
	while (pElmFrame)
	{
		IMAGE_FRAME imageFrame;

		const char* pszFrameName = pElmFrame->Attribute("id");
		if (!pszFrameName) return false;

		// TODO: check pszFrameName exist ?

		for (int i = 0; i < IFB_NUM; ++i)
		{
			TiXmlElement* pElmPiece = pElmFrame->FirstChildElement(s_FramePieces[i]);
			if (!pElmPiece) return false;

			const char* pszPieceName = pElmPiece->Attribute("id");
			if (!pszPieceName) return false;

			imageFrame.pImagePiece[i] = IResourceMgr::GetInstance().FindImagePiece(pszPieceName);
			if (!imageFrame.pImagePiece[i]) return false;
		}

		m_mapImageFrame.insert(std::make_pair(pszFrameName, imageFrame));

		pElmFrame = pElmFrame->NextSiblingElement("Frame");
	}

	return true;
}

const IMAGE_FRAME* UIResMgr_Impl::FindImageFrame(const char* pszFrameName) const
{
	TM_IMAGE_FRAME::const_iterator itfound = m_mapImageFrame.find(pszFrameName);
	if (itfound == m_mapImageFrame.end()) return NULL;

	return &itfound->second;
}

const IMAGE_FRAME* UIResMgr_Impl::GetDefaultImageFrame() const
{
	return m_pDefaultFrame;
}

const IMAGE_FRAME* UIResMgr_Impl::GetPressedImageFrame() const
{
	// TODO: return a pressed image frame
	return m_pDefaultFrame;
}

const IMAGE_FRAME* UIResMgr_Impl::GetDisabledImageFrame() const
{
	// TODO: return a disabled image frame
	return m_pDefaultFrame;
}

bool UIResMgr_Impl::SetupDefaultButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece /*= DUS_BUTTON_NUM*/) const
{
	if (nPiece != DUS_BUTTON_NUM)
	{
		LOGE("boundary out of range");
		return false;
	}

	for (int i = 0; i < DUS_BUTTON_NUM; ++i)
	{
		pPieceOut[i] = m_pButtonStyle[i];
	}

	return true;
}

bool UIResMgr_Impl::SetupDefaultCheckButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece /*= DUS_CHECKBUTTON_NUM*/) const
{
	if (nPiece != DUS_CHECKBUTTON_NUM)
	{
		LOGE("boundary out of range");
		return false;
	}

	for (int i = 0; i < DUS_CHECKBUTTON_NUM; ++i)
	{
		pPieceOut[i] = m_pCheckButtonStyle[i];
	}

	return true;
}

bool UIResMgr_Impl::SetupDefaultRadioButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece /*= DUS_RADIOBUTTON_NUM*/) const
{
	if (nPiece != DUS_RADIOBUTTON_NUM)
	{
		LOGE("boundary out of range");
		return false;
	}

	for (int i = 0; i < DUS_RADIOBUTTON_NUM; ++i)
	{
		pPieceOut[i] = m_pRadioButtonStyle[i];
	}

	return true;
}
bool UIResMgr_Impl::SetupDefaultSliderBarTextures( const IMAGE_PIECE** pPirceOut, int nPiece /*= DUS_SLIDERBAR_NUM*/ ) const
{
	if(nPiece != DUS_SLIDERBAR_NUM)
	{
		LOGE("boundary out of range");
		return false;
	}
	for (int i = 0; i< DUS_SLIDERBAR_NUM; i++)
	{
		pPirceOut[i] = m_pSliderBarStyle[i];
	}
	
	return true;
}
IFont* UIResMgr_Impl::FindFont(const char* pszFontFile)
{
	TM_FONT::iterator itfound = m_mapFont.find(pszFontFile);
	if (itfound == m_mapFont.end()) return NULL;

	return itfound->second;
}

bool UIResMgr_Impl::OnFontDestroied(IMsgBase* pMsg)
{
	MsgCommon* pMsgCommon = (MsgCommon*)pMsg;
	IFont* pFont = (IFont*)pMsgCommon->GetObject();
	if (!pFont) return false;

	for (TM_FONT::iterator it = m_mapFont.begin(); it != m_mapFont.end(); ++it)
	{
		if (it->second == pFont)
		{
			m_mapFont.erase(it);
			return true;
		}
	}

	return false;
}

bool UIResMgr_Impl::InitDefaultButtonStyle()
{
	static const char* s_pszImagePieces[DUS_BUTTON_NUM] = 
	{
		"ui_button_default",
		"ui_button_pressed",
		"ui_button_disabled",
	};

	for (int i = 0; i < DUS_BUTTON_NUM; ++i)
	{
		m_pButtonStyle[i] = IResourceMgr::GetInstance().FindImagePiece(s_pszImagePieces[i]);
		if (!m_pButtonStyle[i]) return false;
	}

	return true;
}

bool UIResMgr_Impl::InitDefaultCheckButtonStyle()
{
	static const char* s_pszImagePieces[DUS_CHECKBUTTON_NUM] = 
	{
		"ui_checkbutton_check",
		"ui_checkbutton_check_pressed",
		"ui_checkbutton_check_disabled",
		"ui_checkbutton_uncheck",
		"ui_checkbutton_uncheck_pressed",
		"ui_checkbutton_uncheck_disabled",
	};

	for (int i = 0; i < DUS_CHECKBUTTON_NUM; ++i)
	{
		m_pCheckButtonStyle[i] = IResourceMgr::GetInstance().FindImagePiece(s_pszImagePieces[i]);
		if (!m_pCheckButtonStyle[i]) return false;
	}

	return true;
}

bool UIResMgr_Impl::InitDefaultRadioButtonStyle()
{
	static const char* s_pszImagePieces[DUS_RADIOBUTTON_NUM] = 
	{
		"ui_radiobutton_check",
		"ui_radiobutton_check_pressed",
		"ui_radiobutton_check_disabled",
		"ui_radiobutton_uncheck",
		"ui_radiobutton_uncheck_pressed",
		"ui_radiobutton_uncheck_disabled",
	};

	for (int i = 0; i < DUS_RADIOBUTTON_NUM; ++i)
	{
		m_pRadioButtonStyle[i] = IResourceMgr::GetInstance().FindImagePiece(s_pszImagePieces[i]);
		if (!m_pRadioButtonStyle[i]) return false;
	}

	return true;
}
bool UIResMgr_Impl::InitDefaultSliderBarStyle()
{
	static const char* s_pszImagePieces[DUS_SLIDERBAR_NUM] = 
	{
		"ui_slider_thumb",
		"ui_slider_thumb",
		"ui_slider_bg",
		"ui_slider_fg",
		"ui_slider_bg",
	};

	for (int i = 0; i < DUS_SLIDERBAR_NUM; i++ )
	{
		m_pSliderBarStyle[i] = IResourceMgr::GetInstance().FindImagePiece(s_pszImagePieces[i]);
		if(!m_pSliderBarStyle[i]) return false;
	}
	
	return true;
}



