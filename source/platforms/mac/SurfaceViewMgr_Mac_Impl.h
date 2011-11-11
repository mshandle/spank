/*!
 * \file SurfaceViewMgr_Mac_Impl.h
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEWMGR_MAC_IMPL__
#define __SURFACEVIEWMGR_MAC_IMPL__

#include <ISurfaceViewMgr.h>

class SurfaceViewMgr_Mac_Impl : public ISurfaceViewMgr
{
public:
	DECLARE_RTTI(SurfaceViewMgr_Mac_Impl, ISurfaceViewMgr);
	
	SurfaceViewMgr_Mac_Impl();
	virtual ~SurfaceViewMgr_Mac_Impl();
	
	virtual bool Initialize();
	virtual void Terminate();
	
	virtual ISurfaceView* CreateSurfaceViewNormal();
	virtual ISurfaceView* CreateSurfaceViewOpenGL();
	
};
#endif // __SURFACEVIEWMGR_MAC_IMPL__
