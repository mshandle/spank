/*!
 * \file SurfaceView_Android_Normal_Impl.cpp
 * \date 11-04-2011 9:39:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceView_Android_Normal_Impl.h"
#include "SpankLibrary.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>

SurfaceView_Android_Normal_Impl::SurfaceView_Android_Normal_Impl()
{
	m_nViewId = 0;
	m_bOK = CreateView();
}

SurfaceView_Android_Normal_Impl::~SurfaceView_Android_Normal_Impl()
{
	// TODO: 
}

bool SurfaceView_Android_Normal_Impl::ActiveView()
{
	// bind current view
	LOGD("active normal view from native, %d", m_nViewId);
	return SpankLibrary::ActiveView(m_nViewId);
}

void SurfaceView_Android_Normal_Impl::DeactiveView()
{
	// unbind current view
	LOGD("de-active normal view from native, %d", m_nViewId);
	SpankLibrary::DeactiveView(m_nViewId);
}

void SurfaceView_Android_Normal_Impl::BeginRender()
{
	// TODO: 
}

void SurfaceView_Android_Normal_Impl::EndRender()
{
	// TODO: 
}

bool SurfaceView_Android_Normal_Impl::CreateView()
{
	// call java method to create view
	m_nViewId = SpankLibrary::CreateNormalView();
	return true;
}

void SurfaceView_Android_Normal_Impl::DestroyView()
{
	// call java method to destroy view
	SpankLibrary::DestroyView(m_nViewId);
	m_nViewId = 0;
}
