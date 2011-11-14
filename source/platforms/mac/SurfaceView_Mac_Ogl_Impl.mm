/*!
 * \file SurfaceView_Mac_Normal_Impl.cpp
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import "SurfaceView_Mac_Ogl_Impl.h"
#import "SpankAppDelegate.h"
#import "util/ConfigUtil.h"
#import "GLES2/gl2.h"

SurfaceView_Mac_Ogl_Impl::SurfaceView_Mac_Ogl_Impl()
{
	m_nViewId = [[SpankAppDelegate GetInstance] createOpenGLView];
	m_bOK = true;
}

SurfaceView_Mac_Ogl_Impl::~SurfaceView_Mac_Ogl_Impl()
{
	// TODO: 
}

int SurfaceView_Mac_Ogl_Impl::GetViewId() const
{
	return m_nViewId;
}

bool SurfaceView_Mac_Ogl_Impl::ActiveView()
{
	if ([[SpankAppDelegate GetInstance] attachView:m_nViewId] == FALSE) return false;
	
	int nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	int nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (nSurfaceWidth <= 0 || nSurfaceHeight <= 0) return false;
	
	glViewport(0, 0, nSurfaceWidth, nSurfaceHeight);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	
	return true;
}

void SurfaceView_Mac_Ogl_Impl::DeactiveView()
{
	[[SpankAppDelegate GetInstance] dettachView:m_nViewId];
}

void SurfaceView_Mac_Ogl_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SurfaceView_Mac_Ogl_Impl::EndRender()
{
	// TODO: 
}
