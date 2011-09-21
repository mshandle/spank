/*!
 * \file UIButton.h
 * \date 2011/09/05 9:31
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __UIBUTTON_H_
#define __UIBUTTON_H_

#include <ui/UIWindow.h>
#include <ui/UIString.h>

#include <ITexture.h>

class UIButton : public UIWindow
{
public:
	DECLARE_RTTI(UIButton, UIWindow);

	UIButton(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ZERO, const char* pszText = NULL);
	virtual ~UIButton();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);
	virtual Vector2 GetBestSize();

	void SetText(const char* pszText);

	bool SetButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex);

	virtual bool OnClicked(const Vector2& pos);

private:
	UIString* m_pString;
	const IMAGE_PIECE* m_pStyle[DUS_BUTTON_NUM];

};
#endif//__UIBUTTON_H_
