/*!
 * \file WinMain.cpp
 * \date 7-21-2011 11:55:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "WinMain.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <ICore.h>
#include <windows.h>

void EnterMessageLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	bool run = true;

	DWORD dwCurrTime = timeGetTime();
	DWORD dwPrevTime = dwCurrTime;

	while (run)
	{
		while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		dwCurrTime = timeGetTime();
		ICore::GetInstance().Update((dwCurrTime - dwPrevTime)/1000.0f);
		ICore::GetInstance().Render();
		dwPrevTime = dwCurrTime;

		run = ICore::GetInstance().IsRunning();
	}
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	ConfigUtil::GetInstance().AddString("WINDOW_CLASS_GDI", "SPANK_GDI");
	ConfigUtil::GetInstance().AddString("WINDOW_CLASS_OGL", "SPANK_OGL");
	ConfigUtil::GetInstance().AddString("WINDOW_TITLE", "spank");
	ConfigUtil::GetInstance().AddString("RESOURCE_DIR", "..\\..\\resources\\");
	ConfigUtil::GetInstance().AddInt("SURFACE_WIDTH", WindowConfig::SURFACE_WIDTH);
	ConfigUtil::GetInstance().AddInt("SURFACE_HEIGHT", WindowConfig::SURFACE_HEIGHT);

	bool bOK = ICore::GetInstance().Initialize();
	if (bOK) EnterMessageLoop();
	ICore::GetInstance().Terminate();

	return 0;
}
