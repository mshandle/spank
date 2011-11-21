/*!
 * \file UIListView.cpp
 * \date 11-21-2011 9:53:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIListView.h>

UIListView::UIListView(UIWindow* pParent, const Vector2& pos /*= IMath::VEC2_ZERO*/)
:UIScrollWindow(pParent, pos)
{
	// TODO: 
}

UIListView::~UIListView()
{
	// TODO: 
}

void UIListView::ArrangeItems()
{
	const Vector2& parentSize = GetSize();
	Vector2 pos(0.0f, 0.0f);

	// set items width
	TV_WINDOW& vChildren = GetChildrenList();
	for (TV_WINDOW::iterator it = vChildren.begin(); it != vChildren.end(); ++it)
	{
		UIWindow* pWindow = (*it);
		const Vector2& size = pWindow->GetSize();
		pWindow->SetSize(parentSize.x, size.y);
		pWindow->SetPosition(pos);
		pos.y += size.y;
	}
}
