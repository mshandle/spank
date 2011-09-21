/*!
 * \file UICheckButton.h
 * \date 2011/09/09 11:23
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UICHECKBUTTON_H__
#define __UICHECKBUTTON_H__

#include "UIWindow.h"
#include "UIString.h"

class UICheckButton : public UIWindow
{
public:
	DECLARE_RTTI(UICheckButton, UIWindow);

	UICheckButton(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ZERO, const char* pszText = NULL);
	virtual ~UICheckButton();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);
	virtual Vector2 GetBestSize();

	void SetText(const char* pszText);

	bool SetCheck(bool bCheck);
	bool IsChecked() const;

	bool SetCheckButtonTexture(const char* pszImageId, int nIndex);
	bool SetCheckButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex);

	virtual bool OnClicked(const Vector2& pos);

private:
	UIString* m_pString;
	bool m_bCheck;
	const IMAGE_PIECE* m_pStyle[DUS_CHECKBUTTON_NUM];

};
#endif // __UICHECKBUTTON_H__
