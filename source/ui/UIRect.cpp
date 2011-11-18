/*!
 * \file UIRect.cpp
 * \date 11-18-2011 9:52:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIRect.h>

UIRect UIRect::UIRECT_ZERO(IMath::VEC2_ZERO, IMath::VEC2_ZERO);

UIRect::UIRect()
{
	// TODO: 
}

UIRect::UIRect(float x, float y, float width, float height)
{
	pos.x = x;
	pos.y = y;
	size.x = width;
	size.y = height;
}

UIRect::UIRect(const Vector2& vPos, const Vector2& vSize)
{
	pos = vPos;
	size = vSize;
}

UIRect::UIRect(const UIRect& rect)
{
	pos = rect.pos;
	size = rect.size;
}

UIRect::~UIRect()
{
	// TODO: 
}

UIRect& UIRect::operator=(const UIRect& rect)
{
	pos = rect.pos;
	size = rect.size;
	return (*this);
}

void UIRect::SetRect(float x, float y, float width, float height)
{
	pos.x = x;
	pos.y = y;
	size.x = width;
	size.y = height;
}

void UIRect::SetRect(const Vector2& vPos, const Vector2& vSize)
{
	pos = vPos;
	size = vSize;
}

void UIRect::SetRect(const UIRect& rect)
{
	pos = rect.pos;
	size = rect.size;
}
