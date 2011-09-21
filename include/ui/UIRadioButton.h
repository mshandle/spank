/*!
 * \file UIRadioButton.h
 * \date 2011/09/08 10:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UIRADIO_H__
#define __UIRADIO_H__

#include "UIWindow.h"
#include "UIString.h"

class UIRadioButton : public UIWindow
{
public:
	DECLARE_RTTI(UIRadioButton, UIWindow);

	UIRadioButton(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ONE, const char* pszText = NULL);
	virtual ~UIRadioButton();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);
	virtual Vector2 GetBestSize();

	void SetGroupID(int nGroup);
	int GetGroupID() const;

	void SetText(const char* pszText);

	bool SetCheck(bool bCheck);
	bool IsChecked() const;

	bool SetRadioButtonTexture(const char* pszImageId, int nIndex);
	bool SetRadioButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex);

	virtual bool OnClicked(const Vector2& pos);

private:
	bool RadioButtonFilter(UIWindow* pWindow, void* pData);

private:
	int m_nGroupID;
	UIString* m_pString;
	bool m_bCheck;
	const IMAGE_PIECE* m_pStyle[DUS_RADIOBUTTON_NUM];

};

#endif // __UIRADIO_H__
