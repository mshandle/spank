/*!
 * \file ISurfaceView.h
 * \date 11-02-2011 13:50:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISURFACEVIEW_H__
#define __ISURFACEVIEW_H__

#include <IObject.h>

class ISurfaceView : public IObject
{
public:
	DECLARE_RTTI(ISurfaceView, IObject);

	virtual int GetViewId() const = 0;
	virtual bool ActiveView() = 0;
	virtual void DeactiveView() = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;

};
#endif // __ISURFACEVIEW_H__
