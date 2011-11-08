/*!
 * \file SurfaceView_Android_Ogl_Impl.h
 * \date 11-04-2011 9:25:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEW_ANDROID_OGL_IMPL_H__
#define __SURFACEVIEW_ANDROID_OGL_IMPL_H__

#include <ISurfaceView.h>

class SurfaceView_Android_Ogl_Impl : public ISurfaceView
{
public:
	DECLARE_RTTI(SurfaceView_Android_Ogl_Impl, ISurfaceView);

	SurfaceView_Android_Ogl_Impl();
	virtual ~SurfaceView_Android_Ogl_Impl();

	virtual int GetSurfaceWidth() const;
	virtual int GetSurfaceHeight() const;

	virtual bool ActiveView();
	virtual void DeactiveView();

	virtual void BeginRender();
	virtual void EndRender();

private:
	bool CreateView();
	void DestroyView();

private:
	int m_nSurfaceWidth;
	int m_nSurfaceHeight;
	int m_nViewId;

};
#endif // __SURFACEVIEW_ANDROID_OGL_IMPL_H__
