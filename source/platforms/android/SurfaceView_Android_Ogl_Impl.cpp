/*!
 * \file SurfaceView_Android_Ogl_Impl.cpp
 * \date 11-04-2011 9:27:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceView_Android_Ogl_Impl.h"
#include "SpankLibrary.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <GLES2/gl2.h>

SurfaceView_Android_Ogl_Impl::SurfaceView_Android_Ogl_Impl()
{
	m_nViewId = 0;
	m_bOK = CreateView();
}

SurfaceView_Android_Ogl_Impl::~SurfaceView_Android_Ogl_Impl()
{
	// TODO: 
}

bool SurfaceView_Android_Ogl_Impl::ActiveView()
{
	// bind opengl to current view
	LOGD("active opengl view from native, %d", m_nViewId);
	if (!SpankLibrary::ActiveView(m_nViewId))
	{
		LOGD("active opengl view from native failed, %d", m_nViewId);
		return false;
	}

	int nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	int nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (nSurfaceWidth <= 0 || nSurfaceHeight <= 0) return false;

	// set view port
	glViewport(0, 0, nSurfaceWidth, nSurfaceHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	return true;
}

void SurfaceView_Android_Ogl_Impl::DeactiveView()
{
	// unbind opengl
	LOGD("de-active opengl view from native, %d", m_nViewId);
	SpankLibrary::DeactiveView(m_nViewId);
}

void SurfaceView_Android_Ogl_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SurfaceView_Android_Ogl_Impl::EndRender()
{
	// TODO: 
}

bool SurfaceView_Android_Ogl_Impl::CreateView()
{
	// call java method to create view
	m_nViewId = SpankLibrary::CreateOpenGLView();
	return true;
}

void SurfaceView_Android_Ogl_Impl::DestroyView()
{
	// call java method to destroy view
	SpankLibrary::DestroyView(m_nViewId);
}
