/*!
 * \file SurfaceViewMgr_Win32_Impl.h
 * \date 11-02-2011 14:58:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEWMGR_WIN32_IMPL_H__
#define __SURFACEVIEWMGR_WIN32_IMPL_H__

#include <ISurfaceViewMgr.h>

class SurfaceViewMgr_Win32_Impl : public ISurfaceViewMgr
{
public:
	DECLARE_RTTI(SurfaceViewMgr_Win32_Impl, ISurfaceViewMgr);

	SurfaceViewMgr_Win32_Impl();
	virtual ~SurfaceViewMgr_Win32_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual ISurfaceView* CreateSurfaceViewNormal();
	virtual ISurfaceView* CreateSurfaceViewOpenGL();

};
#endif // __SURFACEVIEWMGR_WIN32_IMPL_H__
