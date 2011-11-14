/*!
 * \file SurfaceView_Win32_Ogl_Impl.cpp
 * \date 11-02-2011 14:13:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceView_Win32_Ogl_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <InputMgr.h>
#include <math/IMath.h>
#include <GLES2/gl2.h>

SurfaceView_Win32_Ogl_Impl::SurfaceView_Win32_Ogl_Impl(HWND hWindow)
{
	m_EGLDisplay = NULL;
	m_EGLSurface = NULL;
	m_EGLContext = NULL;
	m_hWindow = hWindow;
	m_bOK = true;
}

SurfaceView_Win32_Ogl_Impl::~SurfaceView_Win32_Ogl_Impl()
{
	// TODO: 
}

int SurfaceView_Win32_Ogl_Impl::GetViewId() const
{
	return 0;
}

bool SurfaceView_Win32_Ogl_Impl::ActiveView()
{
	// bind opengl es to window
	if (!InitializeEGL()) return false;

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

void SurfaceView_Win32_Ogl_Impl::DeactiveView()
{
	TerminateEGL();

	HWND hWindow = (HWND)ConfigUtil::GetInstance().GetPointer("NATIVE_WINDOW", NULL);
	if (hWindow) InvalidateRect(hWindow, NULL, TRUE);
}

void SurfaceView_Win32_Ogl_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glClearColor error code: 0x%04x", eError);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glClear error code: 0x%04x", eError);
}

void SurfaceView_Win32_Ogl_Impl::EndRender()
{
	glFlush();
	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glFlush error code: 0x%04x", eError);

	eglSwapBuffers(m_EGLDisplay, m_EGLSurface);
}

bool SurfaceView_Win32_Ogl_Impl::InitializeEGL()
{
	static const EGLint s_EGLAttributes[] =
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	static const EGLint s_EGLContextAttributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	if (IsEGLInitialized()) return true;

	HDC hDisplay = GetDC(NULL);
	if (!hDisplay) return false;

	m_EGLDisplay = eglGetDisplay(hDisplay);
	eglInitialize(m_EGLDisplay, NULL, NULL);

	EGLint numEGLConfigs = 0;
	EGLConfig eglConfigs[1] = {NULL};
	eglChooseConfig(m_EGLDisplay, s_EGLAttributes, eglConfigs, 1, &numEGLConfigs);

	m_EGLSurface = eglCreateWindowSurface(m_EGLDisplay, eglConfigs[0], (EGLNativeWindowType)m_hWindow, NULL);
	if (m_EGLSurface == EGL_NO_SURFACE) return false;

	m_EGLContext = eglCreateContext(m_EGLDisplay, eglConfigs[0], EGL_NO_CONTEXT, s_EGLContextAttributes);
	if (m_EGLContext == EGL_NO_CONTEXT) return false;

	eglMakeCurrent(m_EGLDisplay, m_EGLSurface, m_EGLSurface, m_EGLContext);

	LOGD("OpenGLES 2.0 initialized");
	return true;
}

void SurfaceView_Win32_Ogl_Impl::TerminateEGL()
{
	if (m_EGLDisplay)
	{
		eglMakeCurrent(m_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroySurface(m_EGLDisplay, m_EGLSurface);
		eglDestroyContext(m_EGLDisplay, m_EGLContext);
		eglTerminate(m_EGLDisplay);
	}

	m_EGLDisplay = NULL;
	m_EGLSurface = NULL;
	m_EGLContext = NULL;

	LOGD("OpenGLES 2.0 terminated");
}

bool SurfaceView_Win32_Ogl_Impl::IsEGLInitialized()
{
	return (m_EGLDisplay != NULL);
}

HWND SurfaceView_Win32_Ogl_Impl::GetWindow() const
{
	return m_hWindow;
}
