/*!
 * \file OSUISystem_Android_Impl.h
 * \date 11-11-2011 14:27:20
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __OSUISYSTEM_ANDROID_IMPL_H__
#define __OSUISYSTEM_ANDROID_IMPL_H__

#include <osui/IOSUISystem.h>

class OSUISystem_Android_Impl : public IOSUISystem
{
public:
	DECLARE_RTTI(OSUISystem_Android_Impl, IOSUISystem);

	OSUISystem_Android_Impl();
	virtual ~OSUISystem_Android_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual int CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height, const char* pszText);
	virtual int CreateEditText(ISurfaceView* pSurfaceView, int x, int y, int width, int height);

	virtual void DestroyControl(ISurfaceView* pSurfaceView, int nId);

};
#endif // __OSUISYSTEM_ANDROID_IMPL_H__
