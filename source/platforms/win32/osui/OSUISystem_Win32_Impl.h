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
#include <map>

class OSUISystem_Win32_Impl : public IOSUISystem
{
public:
	enum CONST_DEFINE
	{
		CONTROL_ID_BASE = 10000,
	};

	typedef std::map<int, void*> TM_CONTROL_ID;

public:
	DECLARE_RTTI(OSUISystem_Win32_Impl, IOSUISystem);

	OSUISystem_Win32_Impl();
	virtual ~OSUISystem_Win32_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual int CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height, const char* pszText);
	virtual void DestroyButton(ISurfaceView* pSurfaceView, int nId);

private:
	int GenNextId();

private:
	int m_nGenNextId;
	TM_CONTROL_ID m_ControlMap;

};
#endif // __OSUISYSTEM_WIN32_IMPL_H__
