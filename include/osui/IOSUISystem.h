/*!
 * \file IOSUISystem.h
 * \date 11-09-2011 14:21:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IOSUISYSTEM_H__
#define __IOSUISYSTEM_H__

#include "../ISingleton.h"
#include "../ISurfaceView.h"

class IOSUISystem : public ISingleton
{
public:
	DECLARE_RTTI(IOSUISystem, ISingleton);

	static IOSUISystem& GetInstance();

	virtual int CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height, const char* pszText) = 0;
	virtual int CreateEditText(ISurfaceView* pSurfaceView, int x, int y, int width, int height) = 0;

	virtual void DestroyControl(ISurfaceView* pSurfaceView, int nId) = 0;

};
#endif // __IOSUISYSTEM_H__
