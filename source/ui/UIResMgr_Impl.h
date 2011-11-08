/*!
 * \file UIResMgr_Impl.h
 * \date 8-22-2011 15:33:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIRESMGR_IMPL_H__
#define __UIRESMGR_IMPL_H__

#include <ui/IUIResMgr.h>
#include <msg/IMsgBase.h>
#include <map>
#include <string>

class UIResMgr_Impl : public IUIResMgr
{
public:
	typedef std::map<std::string, IFont*> TM_FONT;
	typedef std::map<std::string, IMAGE_FRAME> TM_IMAGE_FRAME;

public:
	DECLARE_RTTI(UIResMgr_Impl, IUIResMgr);

	UIResMgr_Impl();
	virtual ~UIResMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual IFont* CreateFont(const char* pszFontFile);
	virtual IFont* GetDefaultFont();

	virtual bool AddImageFrame(const char* pszFrameFile);
	virtual const IMAGE_FRAME* FindImageFrame(const char* pszFrameName) const;

	virtual const IMAGE_FRAME* GetDefaultImageFrame() const;
	virtual const IMAGE_FRAME* GetPressedImageFrame() const;
	virtual const IMAGE_FRAME* GetDisabledImageFrame() const;

	virtual bool SetupDefaultButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_BUTTON_NUM) const;
	virtual bool SetupDefaultCheckButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_CHECKBUTTON_NUM) const;
	virtual bool SetupDefaultRadioButtonTextures(const IMAGE_PIECE** pPieceOut, int nPiece = DUS_RADIOBUTTON_NUM) const;
	virtual bool SetupDefaultSliderBarTextures(const IMAGE_PIECE** pPirceOut, int nPiece = DUS_SLIDERBAR_NUM) const;

private:
	IFont* FindFont(const char* pszFontFile);
	bool OnFontDestroied(IMsgBase* pMsg);

	bool InitDefaultButtonStyle();
	bool InitDefaultCheckButtonStyle();
	bool InitDefaultRadioButtonStyle();
	bool InitDefaultSliderBarStyle();

	void ZeroData();

private:
	TM_FONT m_mapFont;
	IFont* m_pDefaultFont;

	const IMAGE_PIECE* m_pButtonStyle[DUS_BUTTON_NUM];
	const IMAGE_PIECE* m_pCheckButtonStyle[DUS_CHECKBUTTON_NUM];
	const IMAGE_PIECE* m_pRadioButtonStyle[DUS_RADIOBUTTON_NUM];
	const IMAGE_PIECE* m_pSliderBarStyle[DUS_SLIDERBAR_NUM];
	TM_IMAGE_FRAME m_mapImageFrame;
	const IMAGE_FRAME* m_pDefaultFrame;

};
#endif // __UIRESMGR_IMPL_H__
