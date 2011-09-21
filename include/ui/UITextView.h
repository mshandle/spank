/*!
 * \file UITextView.h
 * \date 8-24-2011 15:23:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UITEXTVIEW_H__
#define __UITEXTVIEW_H__

#include "UIWindow.h"
#include "UIString.h"

class UITextView : public UIWindow
{
public:
	DECLARE_RTTI(UITextView, UIWindow);

	UITextView(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ZERO, const char* pszText = NULL);
	virtual ~UITextView();

	void SetText(const char* pszText);

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);
	virtual Vector2 GetBestSize();

	virtual bool OnClicked(const Vector2& pos);

private:
	UIString* m_pString;

};
#endif // __UITEXTVIEW_H__
