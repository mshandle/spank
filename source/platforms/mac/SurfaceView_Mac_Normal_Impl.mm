/*!
 * \file SurfaceView_Mac_Normal_Impl.cpp
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import "SurfaceView_Mac_Normal_Impl.h"
#import "SpankAppDelegate.h"

SurfaceView_Mac_Normal_Impl::SurfaceView_Mac_Normal_Impl()
{
	m_nViewId = [[SpankAppDelegate GetInstance] createNormalView];
	m_bOK = true;
}

SurfaceView_Mac_Normal_Impl::~SurfaceView_Mac_Normal_Impl()
{
	// TODO: 
}

bool SurfaceView_Mac_Normal_Impl::ActiveView()
{
	if ([[SpankAppDelegate GetInstance] attachView:m_nViewId] == TRUE) return true;
	return false;
}

void SurfaceView_Mac_Normal_Impl::DeactiveView()
{
	[[SpankAppDelegate GetInstance] dettachView:m_nViewId];
}

void SurfaceView_Mac_Normal_Impl::BeginRender()
{
	// TODO: 
}

void SurfaceView_Mac_Normal_Impl::EndRender()
{
	// TODO: 
}
