/*!
 * \file OSUISystem_Win32_Impl.h
 * \date 11-09-2011 14:21:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __OSUISYSTEM_WIN32_IMPL_H__
#define __OSUISYSTEM_WIN32_IMPL_H__

#include <osui/IOSUISystem.h>

class OSUISystem_Win32_Impl : public IOSUISystem
{
public:
	DECLARE_RTTI(OSUISystem_Win32_Impl, IOSUISystem);

	OSUISystem_Win32_Impl();
	virtual ~OSUISystem_Win32_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void* CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height);
	virtual void DestroyButton(void* pHandler);

private:
	int GenNextId();

private:
	int m_nGenNextId;

};
#endif // __OSUISYSTEM_WIN32_IMPL_H__
