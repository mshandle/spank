/*!
 * \file UIListView.h
 * \date 11-21-2011 9:52:56
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UILISTVIEW_H__
#define __UILISTVIEW_H__

#include "UIScrollWindow.h"

class UIListView : public UIScrollWindow
{
public:
	DECLARE_RTTI(UIListView, UIScrollWindow);

	UIListView(UIWindow* pParent, const Vector2& pos = IMath::VEC2_ZERO);
	virtual ~UIListView();

	void ArrangeItems();

};
#endif // __UILISTVIEW_H__
