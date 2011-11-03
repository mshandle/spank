/*!
 * \file ISurfaceViewMgr.h
 * \date 11-02-2011 14:59:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISURFACEVIEWMGR_H__
#define __ISURFACEVIEWMGR_H__

#include "ISingleton.h"
#include "ISurfaceView.h"

class ISurfaceViewMgr : public ISingleton
{
public:
	DECLARE_RTTI(ISurfaceViewMgr, ISingleton);

	static ISurfaceViewMgr& GetInstance();

	virtual ISurfaceView* CreateSurfaceViewNormal() = 0;
	virtual ISurfaceView* CreateSurfaceViewOpenGL() = 0;
};
#endif // __ISURFACEVIEWMGR_H__
