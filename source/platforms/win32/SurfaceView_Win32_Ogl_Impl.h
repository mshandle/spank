/*!
 * \file SurfaceView_Win32_Ogl_Impl.h
 * \date 11-02-2011 14:12:56
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEW_WIN32_OGL_IMPL_H__
#define __SURFACEVIEW_WIN32_OGL_IMPL_H__

#include <ISurfaceView.h>
#include <windows.h>
#include <EGL/egl.h>

class SurfaceView_Win32_Ogl_Impl : public ISurfaceView
{
public:
	DECLARE_RTTI(SurfaceView_Win32_Ogl_Impl, ISurfaceView);

	SurfaceView_Win32_Ogl_Impl(HWND hWindow);
	virtual ~SurfaceView_Win32_Ogl_Impl();

	virtual int GetViewId() const;

	virtual bool ActiveView();
	virtual void DeactiveView();

	virtual void BeginRender();
	virtual void EndRender();

	HWND GetWindow() const;

private:
	bool InitializeEGL();
	void TerminateEGL();
	bool IsEGLInitialized();

private:
	EGLDisplay m_EGLDisplay;
	EGLSurface m_EGLSurface;
	EGLContext m_EGLContext;
	HWND m_hWindow;

};
#endif // __SURFACEVIEW_WIN32_OGL_IMPL_H__
