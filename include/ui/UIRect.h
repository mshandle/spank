/*!
 * \file UIRect.h
 * \date 11-18-2011 9:52:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIRECT_H__
#define __UIRECT_H__

#include "../math/IMath.h"

class UIRect
{
public:
	UIRect();
	UIRect(float x, float y, float width, float height);
	UIRect(const Vector2& vPos, const Vector2& vSize);
	UIRect(const UIRect& rect);
	~UIRect();

	UIRect& operator=(const UIRect& rect);

	void SetRect(float x, float y, float width, float height);
	void SetRect(const Vector2& vPos, const Vector2& vSize);
	void SetRect(const UIRect& rect);

public:
	Vector2 pos;
	Vector2 size;

	static UIRect UIRECT_ZERO;

};

#endif // __UIRECT_H__
