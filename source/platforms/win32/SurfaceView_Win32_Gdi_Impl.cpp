/*!
 * \file SurfaceView_Win32_Gdi_Impl.cpp
 * \date 11-02-2011 14:10:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceView_Win32_Gdi_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <InputMgr.h>
#include <math/IMath.h>

SurfaceView_Win32_Gdi_Impl::SurfaceView_Win32_Gdi_Impl(HWND hWindow)
{
	m_hWindow = hWindow;
	m_bOK = true;
}

SurfaceView_Win32_Gdi_Impl::~SurfaceView_Win32_Gdi_Impl()
{
	// TODO: 
}

bool SurfaceView_Win32_Gdi_Impl::ActiveView()
{
	return true;
}

void SurfaceView_Win32_Gdi_Impl::DeactiveView()
{
	// TODO: 
}

void SurfaceView_Win32_Gdi_Impl::BeginRender()
{
	// TODO: 
}

void SurfaceView_Win32_Gdi_Impl::EndRender()
{
	// TODO: 
}

HWND SurfaceView_Win32_Gdi_Impl::GetWindow() const
{
	return m_hWindow;
}
