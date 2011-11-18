/*!
 * \file UIScrollWindow.h
 * \date 11-18-2011 9:07:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UISCROLLWINDOW_H__
#define __UISCROLLWINDOW_H__

#include "UIWindow.h"

class UIScrollWindow : public UIWindow
{
public:
	DECLARE_RTTI(UIScrollWindow, UIWindow);

	UIScrollWindow(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ZERO);
	virtual ~UIScrollWindow();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

	virtual void SetSize(float width, float height);
	virtual Vector2 GetBestSize();

	virtual bool ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType);

protected:
	virtual void AddChild(UIWindow* pWindow);
	virtual void RemoveChild(UIWindow* pWindow);
	void UpdateVirtualPosAndSize();

	virtual void RenderChildrenWindow(const RenderParam& param);
	virtual void RenderBorder(const RenderParam& param);

private:
	Vector2 m_vScrollOffset;
	Vector2 m_vScrollOffsetBackup;
	Vector2 m_vTouchPos;
	UIRect m_vVirtualRect;

	UIWindow* m_pLastTouchedWindow;

};
#endif // __UISCROLLWINDOW_H__
