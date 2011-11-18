/*!
 * \file UIWindow.h
 * \date 8-24-2011 14:52:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

#include "../IObject.h"
#include "BaseTypeUI.h"
#include "RenderParam.h"

#include <vector>

class UIWindow;
typedef bool (IMsgHandler::*ENUM_WINDOW_FILTER)(UIWindow* pWindow, void* pData);

class UIWindow : public IObject
{
public:
	enum WINDOW_STATE
	{
		WS_VISIBLE				= 0x00000001,
		WS_ENABLE				= 0x00000002,
		WS_AUTO_ADJUST_SIZE		= 0x00000004,
		WS_PRESSED				= 0x00000008,
		WS_DEFAULT_STATE		= WS_VISIBLE | WS_ENABLE | WS_AUTO_ADJUST_SIZE,
	};

	typedef std::vector<UIWindow*> TV_WINDOW;

public:
	DECLARE_RTTI(UIWindow, IObject);

	UIWindow(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ZERO);
	virtual ~UIWindow();

	virtual void Update(float dt) = 0;
	virtual void Render(const RenderParam& param) = 0;
	virtual Vector2 GetBestSize() = 0;

	UIWindow* GetParentWindow();

	int GetID() const;
	void SetID(int nID);

	const Vector2& GetPosition() const;
	virtual Vector2 GetPositionAbsolute();
	virtual void SetPosition(const Vector2& pos);
	virtual void SetPosition(float x, float y);

	const Vector2& GetSize() const;
	void SetSize(const Vector2& size);
	virtual void SetSize(float width, float height);

	void SetMargin(float left, float top, float right, float bottom);
	const Vector2& GetMarginLeftTop() const;
	const Vector2& GetMarginRightBottom() const;

	void SetWindowState(uint nMask, bool bSet);
	bool CheckWindowState(uint nMask) const;

	void SetVisible(bool bVisible);
	bool IsVisible() const;

	void SetEnable(bool bEnable);
	bool IsEnable() const;

	void SetAutoAdjustSize(bool bAutoAdjustSize);
	bool IsAutoAdjustSize() const;

	bool IsPressed() const;

	void AdjustSize();

	virtual bool ProcessTouchEvent(const Vector2& pos, UI_TOUCH_EVENT_TYPE eType);

	UIWindow* FindChildWindow(int nID);
	bool EnumlateChildrenWindows(TV_WINDOW& vWindowsOut, IMsgHandler* pHandler, ENUM_WINDOW_FILTER pCallback, void* pCustomData);

	virtual bool OnClicked(const Vector2& pos);
	virtual bool OnTouchBegin(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);
	virtual void OnTouchLost();
	
protected:
	virtual void AddChild(UIWindow* pWindow);
	virtual void RemoveChild(UIWindow* pWindow);
	virtual TV_WINDOW& GetChildrenList();

	virtual void UpdateChildrenWindow(float dt);
	virtual void RenderChildrenWindow(const RenderParam& param);
	virtual void RenderBorder(const RenderParam& param);

	virtual UIWindow* FindChildUnderPoint(const Vector2& pos);

private:
	TV_WINDOW m_vChildren;

	int m_nID;

	Vector2 m_vPosition;
	Vector2 m_vSize;

	Vector2 m_MarginLeftTop;
	Vector2 m_MarginRightBottom;

	uint m_nState;

	UIWindow* m_pLastTouchedWindow;

};
#endif // __UIWINDOW_H__
