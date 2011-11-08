/*!
 * \file SurfaceView_Android_Normal_Impl.h
 * \date 11-04-2011 9:36:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEW_ANDROID_NORMAL_IMPL_H__
#define __SURFACEVIEW_ANDROID_NORMAL_IMPL_H__

#include <ISurfaceView.h>

class SurfaceView_Android_Normal_Impl : public ISurfaceView
{
public:
	DECLARE_RTTI(SurfaceView_Android_Normal_Impl, ISurfaceView);

	SurfaceView_Android_Normal_Impl();
	virtual ~SurfaceView_Android_Normal_Impl();

	virtual bool ActiveView();
	virtual void DeactiveView();

	virtual void BeginRender();
	virtual void EndRender();

private:
	bool CreateView();
	void DestroyView();

private:
	int m_nViewId;

};
#endif // __SURFACEVIEW_ANDROID_NORMAL_IMPL_H__
