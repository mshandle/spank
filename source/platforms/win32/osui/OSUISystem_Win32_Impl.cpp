/*!
 * \file OSUISystem_Win32_Impl.cpp
 * \date 11-10-2011 9:52:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "OSUISystem_Win32_Impl.h"
#include "../SurfaceView_Win32_Gdi_Impl.h"

IOSUISystem& IOSUISystem::GetInstance()
{
	static OSUISystem_Win32_Impl s_OSUISystem_Win32_Impl;
	return s_OSUISystem_Win32_Impl;
}

OSUISystem_Win32_Impl::OSUISystem_Win32_Impl()
{
	m_nGenNextId = CONTROL_ID_BASE;
}

OSUISystem_Win32_Impl::~OSUISystem_Win32_Impl()
{
	// TODO: 
}

bool OSUISystem_Win32_Impl::Initialize()
{
	m_nGenNextId = CONTROL_ID_BASE;
	return true;
}

void OSUISystem_Win32_Impl::Terminate()
{
	// TODO: 
}

int OSUISystem_Win32_Impl::CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height, const char* pszText)
{
	if (!pSurfaceView->GetRtti()->IsDerived(SurfaceView_Win32_Gdi_Impl::__RttiData())) return 0;

	SurfaceView_Win32_Gdi_Impl* pGdiView = (SurfaceView_Win32_Gdi_Impl*)pSurfaceView;
	HWND hParent = pGdiView->GetWindow();

	int nId = GenNextId();
	HWND hWnd = CreateWindow("BUTTON", pszText, WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, width, height, hParent, (HMENU)nId, NULL, NULL);

	m_ControlMap.insert(std::make_pair(nId, hWnd));
	return nId;
}

int OSUISystem_Win32_Impl::CreateEditText(ISurfaceView* pSurfaceView, int x, int y, int width, int height)
{
	if (!pSurfaceView->GetRtti()->IsDerived(SurfaceView_Win32_Gdi_Impl::__RttiData())) return 0;

	SurfaceView_Win32_Gdi_Impl* pGdiView = (SurfaceView_Win32_Gdi_Impl*)pSurfaceView;
	HWND hParent = pGdiView->GetWindow();

	int nId = GenNextId();
	HWND hWnd = CreateWindow("EDIT", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, x, y, width, height, hParent, (HMENU)nId, NULL, NULL);

	m_ControlMap.insert(std::make_pair(nId, hWnd));
	return nId;
}

void OSUISystem_Win32_Impl::DestroyControl(ISurfaceView* pSurfaceView, int nId)
{
	TM_CONTROL_ID::iterator itfound = m_ControlMap.find(nId);
	if (itfound == m_ControlMap.end()) return;

	HWND hWnd = (HWND)itfound->second;
	DestroyWindow(hWnd);

	m_ControlMap.erase(itfound);
}

int OSUISystem_Win32_Impl::GenNextId()
{
	return m_nGenNextId++;
}
