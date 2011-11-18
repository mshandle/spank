/*!
 * \file RenderParam.cpp
 * \date 8-25-2011 15:53:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/RenderParam.h>

RenderParam::RenderParam()
{
	// TODO: 
}

RenderParam::RenderParam(const Vector2& renderOffset, const UIRect& parentRect)
{
	m_renderOffset = renderOffset;
	m_parentRect = parentRect;
	m_nRenderState = URS_DEFAULT;
}

RenderParam::RenderParam(const RenderParam& param)
{
	m_renderOffset = param.m_renderOffset;
	m_parentRect = param.m_parentRect;
	m_nRenderState = URS_DEFAULT;
}

RenderParam::~RenderParam()
{
	// TODO: 
}

RenderParam& RenderParam::operator=(const RenderParam& param)
{
	m_renderOffset = param.m_renderOffset;
	m_parentRect = param.m_parentRect;
	m_nRenderState = param.m_nRenderState;
	return (*this);
}

void RenderParam::SetRenderState(uint nMask, bool bEnable)
{
	if (bEnable)
	{
		m_nRenderState |= nMask;
	}
	else
	{
		m_nRenderState &= (~nMask);
	}
}

bool RenderParam::CheckRenderState(uint nMask) const
{
	return (nMask & m_nRenderState) == nMask;
}

void RenderParam::SetEnable(bool bEnable)
{
	SetRenderState(URS_ENABLE, bEnable);
}

bool RenderParam::IsEnable() const
{
	return CheckRenderState(URS_ENABLE);
}
