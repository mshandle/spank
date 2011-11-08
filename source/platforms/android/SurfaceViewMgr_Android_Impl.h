/*!
 * \file SurfaceViewMgr_Android_Impl.h
 * \date 11-04-2011 9:45:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEWMGR_ANDROID_IMPL_H__
#define __SURFACEVIEWMGR_ANDROID_IMPL_H__

#include <ISurfaceViewMgr.h>

class SurfaceViewMgr_Android_Impl : public ISurfaceViewMgr
{
public:
	DECLARE_RTTI(SurfaceViewMgr_Android_Impl, ISurfaceViewMgr);

	SurfaceViewMgr_Android_Impl();
	virtual ~SurfaceViewMgr_Android_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual ISurfaceView* CreateSurfaceViewNormal();
	virtual ISurfaceView* CreateSurfaceViewOpenGL();

};
#endif // __SURFACEVIEWMGR_ANDROID_IMPL_H__
