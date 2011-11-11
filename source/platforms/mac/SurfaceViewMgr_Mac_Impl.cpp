/*!
 * \file SurfaceViewMgr_Mac_Impl.cpp
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceViewMgr_Mac_Impl.h"
#include "SurfaceView_Mac_Normal_Impl.h"
#include "SurfaceView_Mac_Ogl_Impl.h"

ISurfaceViewMgr& ISurfaceViewMgr::GetInstance()
{
	static SurfaceViewMgr_Mac_Impl s_SurfaceViewMgr_Mac_Impl;
	return s_SurfaceViewMgr_Mac_Impl;
}

SurfaceViewMgr_Mac_Impl::SurfaceViewMgr_Mac_Impl()
{
	// TODO: 
}

SurfaceViewMgr_Mac_Impl::~SurfaceViewMgr_Mac_Impl()
{
	// TODO: 
}

bool SurfaceViewMgr_Mac_Impl::Initialize()
{
	return true;
}

void SurfaceViewMgr_Mac_Impl::Terminate()
{
	// TODO: 
}

ISurfaceView* SurfaceViewMgr_Mac_Impl::CreateSurfaceViewNormal()
{
	// TODO: cache the view
	return new SurfaceView_Mac_Normal_Impl();
}

ISurfaceView* SurfaceViewMgr_Mac_Impl::CreateSurfaceViewOpenGL()
{
	// TODO: cache the view
	return new SurfaceView_Mac_Ogl_Impl();
}
