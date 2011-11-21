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
	enum SCROLL_WINDOW_STATE
	{
		SWS_VSCROLL = 0x00000001,
		SWS_HSCROLL = 0x00000002,
		SWS_MOUSE_MOVED = 0x00000004,
		SWS_DEFAULT = SWS_VSCROLL,
	};

public:
	DECLARE_RTTI(UIScrollWindow, UIWindow);

	UIScrollWindow(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ZERO);
	virtual ~UIScrollWindow();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

	virtual Vector2 GetBestSize();

	virtual bool ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType);

	void SetScrollWindowState(uint nMask, bool bSet);
	bool CheckScrollWindowState(uint nMask) const;

	void UpdateVirtualRect();

protected:
	virtual void RenderChildrenWindow(const RenderParam& param);
	virtual void RenderBorder(const RenderParam& param);

private:
	Vector2 m_vScrollOffset;
	Vector2 m_vScrollOffsetBackup;
	Vector2 m_vTouchPos;
	UIRect m_vVirtualRect;
	
	UIWindow* m_pLastTouchedWindow;
	uint m_nScrollWindowFlag;

};
#endif // __UISCROLLWINDOW_H__
