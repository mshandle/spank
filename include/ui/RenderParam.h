/*!
 * \file RenderParam.h
 * \date 8-25-2011 15:53:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERPARAM_H__
#define __RENDERPARAM_H__

#include "../math/IMath.h"
#include "BaseTypeUI.h"
#include "UIRect.h"

class RenderParam
{
public:
	RenderParam();
	RenderParam(const Vector2& renderOffset, const UIRect& parentRect);
	RenderParam(const RenderParam& param);
	~RenderParam();

	RenderParam& operator=(const RenderParam& param);

	void SetRenderState(uint nMask, bool bEnable);
	bool CheckRenderState(uint nMask) const;

	void SetEnable(bool bEnable);
	bool IsEnable() const;

public:
	Vector2 m_renderOffset;
	UIRect m_parentRect;
	uint m_nRenderState;

};
#endif // __RENDERPARAM_H__
