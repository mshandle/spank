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
	m_nGenNextId = 1000;
}

OSUISystem_Win32_Impl::~OSUISystem_Win32_Impl()
{
	// TODO: 
}

bool OSUISystem_Win32_Impl::Initialize()
{
	m_nGenNextId = 1000;
	return true;
}

void OSUISystem_Win32_Impl::Terminate()
{
	// TODO: 
}

void* OSUISystem_Win32_Impl::CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height)
{
	if (!pSurfaceView->GetRtti()->IsDerived(SurfaceView_Win32_Gdi_Impl::__RttiData())) return NULL;

	SurfaceView_Win32_Gdi_Impl* pGdiView = (SurfaceView_Win32_Gdi_Impl*)pSurfaceView;
	HWND hParent = pGdiView->GetWindow();

	HWND hWnd = CreateWindow("BUTTON", "Button", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, x, y, width, height, hParent, (HMENU)GenNextId(), NULL, NULL);
	return (void*)hWnd;
}

void OSUISystem_Win32_Impl::DestroyButton(void* pHandler)
{
	if (!pHandler) return;

	HWND hWnd = (HWND)pHandler;
	DestroyWindow(hWnd);
}

int OSUISystem_Win32_Impl::GenNextId()
{
	return m_nGenNextId++;
}