/*!
 * \file SurfaceViewMgr_Android_Impl.cpp
 * \date 11-04-2011 9:46:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceViewMgr_Android_Impl.h"
#include "SurfaceView_Android_Normal_Impl.h"
#include "SurfaceView_Android_Ogl_Impl.h"

ISurfaceViewMgr& ISurfaceViewMgr::GetInstance()
{
	static SurfaceViewMgr_Android_Impl s_SurfaceViewMgr_Android_Impl;
	return s_SurfaceViewMgr_Android_Impl;
}

SurfaceViewMgr_Android_Impl::SurfaceViewMgr_Android_Impl()
{
	// TODO: 
}

SurfaceViewMgr_Android_Impl::~SurfaceViewMgr_Android_Impl()
{
	// TODO: 
}

bool SurfaceViewMgr_Android_Impl::Initialize()
{
	return true;
}

void SurfaceViewMgr_Android_Impl::Terminate()
{
	// TODO: 
}

ISurfaceView* SurfaceViewMgr_Android_Impl::CreateSurfaceViewNormal()
{
	// TODO: cache the object
	return new SurfaceView_Android_Normal_Impl();
}

ISurfaceView* SurfaceViewMgr_Android_Impl::CreateSurfaceViewOpenGL()
{
	// TODO: cache the object
	return new SurfaceView_Android_Ogl_Impl();
}
