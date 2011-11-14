/*!
 * \file OSUISystem_Mac_Impl.h
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __OSUISYSTEM_MAC_IMPL_H__
#define __OSUISYSTEM_MAC_IMPL_H__

#include <osui/IOSUISystem.h>

class OSUISystem_Mac_Impl : public IOSUISystem
{
public:
	DECLARE_RTTI(OSUISystem_Mac_Impl, IOSUISystem);
	
	OSUISystem_Mac_Impl();
	virtual ~OSUISystem_Mac_Impl();
	
	virtual bool Initialize();
	virtual void Terminate();
	
	virtual int CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height, const char* pszText);
	virtual void DestroyButton(ISurfaceView* pSurfaceView, int nId);
	
};
#endif // __OSUISYSTEM_MAC_IMPL_H__