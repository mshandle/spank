/*!
 * \file SurfaceView_Mac_Normal_Impl.h
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEW_MAC_NORMAL_IMPL_H__
#define __SURFACEVIEW_MAC_NORMAL_IMPL_H__

#import <ISurfaceView.h>

class SurfaceView_Mac_Normal_Impl : public ISurfaceView
{
public:
	DECLARE_RTTI(SurfaceView_Mac_Normal_Impl, ISurfaceView);
	
	SurfaceView_Mac_Normal_Impl();
	virtual ~SurfaceView_Mac_Normal_Impl();
	
	virtual int GetViewId() const;
	
	virtual bool ActiveView();
	virtual void DeactiveView();
	
	virtual void BeginRender();
	virtual void EndRender();
	
private:
	int m_nViewId;
	
};
#endif // __SURFACEVIEW_MAC_NORMAL_IMPL_H__
