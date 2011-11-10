/*!
 * \file SurfaceViewMgr_Win32_Impl.cpp
 * \date 11-03-2011 11:11:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceViewMgr_Win32_Impl.h"
#include <util/ConfigUtil.h>
#include "SurfaceView_Win32_Gdi_Impl.h"
#include "SurfaceView_Win32_Ogl_Impl.h"

ISurfaceViewMgr& ISurfaceViewMgr::GetInstance()
{
	static SurfaceViewMgr_Win32_Impl s_SurfaceViewMgr_Win32_Impl;
	return s_SurfaceViewMgr_Win32_Impl;
}

SurfaceViewMgr_Win32_Impl::SurfaceViewMgr_Win32_Impl()
{
	// TODO: 
}

SurfaceViewMgr_Win32_Impl::~SurfaceViewMgr_Win32_Impl()
{
	// TODO: 
}

bool SurfaceViewMgr_Win32_Impl::Initialize()
{
	// TODO: 
	return true;
}

void SurfaceViewMgr_Win32_Impl::Terminate()
{
	// TODO: 
}

ISurfaceView* SurfaceViewMgr_Win32_Impl::CreateSurfaceViewNormal()
{
	HWND hWindow = (HWND)ConfigUtil::GetInstance().GetPointer("NATIVE_WINDOW", NULL);
	if (!hWindow) return NULL;

	// TODO: reference the view
	return new SurfaceView_Win32_Gdi_Impl(hWindow);
}

ISurfaceView* SurfaceViewMgr_Win32_Impl::CreateSurfaceViewOpenGL()
{
	HWND hWindow = (HWND)ConfigUtil::GetInstance().GetPointer("NATIVE_WINDOW", NULL);
	if (!hWindow) return NULL;

	// TODO: reference the view
	return new SurfaceView_Win32_Ogl_Impl(hWindow);
}
