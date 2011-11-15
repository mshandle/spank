/*!
 * \file WinMain.cpp
 * \date 7-21-2011 11:55:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "WinMain.h"
#include <util/ConfigUtil.h>
#include <util/ScreenUtil.h>
#include <util/IDebugUtil.h>
#include <InputMgr.h>
#include <ICore.h>
#include <net/INetMgr.h>
#include <windows.h>

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_LBUTTONDOWN:
		{
			int nPosX = (int)(short)LOWORD(lParam);
			int nPosY = (int)(short)HIWORD(lParam);
			Vector2 vPos;
			ScreenUtil::GetInstance().DevicePointToScreen(vPos, (float)nPosX, (float)nPosY);
			InputMgr::GetInstance().OnTouchStart(0, vPos.x, vPos.y);
		}
		break;
	case WM_MOUSEMOVE:
		{
			int nPosX = (int)(short)LOWORD(lParam);
			int nPosY = (int)(short)HIWORD(lParam);
			Vector2 vPos;
			ScreenUtil::GetInstance().DevicePointToScreen(vPos, (float)nPosX, (float)nPosY);
			InputMgr::GetInstance().OnTouchMove(0, vPos.x, vPos.y);
		}
		break;
	case WM_LBUTTONUP:
		{
			int nPosX = (int)(short)LOWORD(lParam);
			int nPosY = (int)(short)HIWORD(lParam);
			Vector2 vPos;
			ScreenUtil::GetInstance().DevicePointToScreen(vPos, (float)nPosX, (float)nPosY);
			InputMgr::GetInstance().OnTouchEnd(0, vPos.x, vPos.y);
		}
		break;
	case WM_KEYDOWN:
		{
			if (wParam == VK_ESCAPE) InputMgr::GetInstance().OnKeyHome();
			if (wParam == VK_BACK) InputMgr::GetInstance().OnKeyReturn();
		}
		break;
	case WindowConfig::WM_SOCKET:
		{
			if (WSAGETSELECTERROR(lParam))
			{
				// display the error and close the socket
				LOGE("WSAGETSELECTERROR(lParam) Error");
				closesocket((SOCKET)wParam);
				break;
			}

			switch (WSAGETSELECTEVENT(lParam))
			{
			case FD_CONNECT:
				{
					LOGD("receive socket connect message");
				}
				break;
			case FD_READ:
				{
					LOGD("receive socket read message");

					SOCKET socket = (SOCKET)wParam;
					char buffer[1024];
					int result = recv(socket, buffer, 1024, 0);

					while (true)
					{
						if (result > 0)
						{
							INetMgr::GetInstance().HandlerDataBlock(buffer, result);
							if (result < 1024) break;
						}
						else
						{
							LOGE("receive data failed result:%d", result);
							break;
						}
						result = recv(socket, buffer, 1024, 0);
					}
				}
				break;
			case FD_WRITE:
				{
					LOGD("receive socket write message");
				}
				break;
			case FD_CLOSE:
				{
					LOGD("receive socket close message");
					closesocket((SOCKET)wParam);
				}
				break;
			default:
				{
					LOGD("receive socket unknown message %d", WSAGETSELECTEVENT(lParam));
				}
				break;
			}
		}
		break;
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			ICore::GetInstance().End();
		}
		break;
	default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	}

	return 0;
}

void DestroyMainWindow(HWND hWindow)
{
	DestroyWindow(hWindow);
}

HWND CreateMainWindow()
{
	int nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	int nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (nSurfaceWidth <= 0 || nSurfaceHeight <= 0) return NULL;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS winClass;
	memset(&winClass, 0, sizeof(winClass));
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC) MainWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = ConfigUtil::GetInstance().GetString("WINDOW_CLASS");
	RegisterClass(&winClass);

	// screen width, height
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// window width, height
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	RECT rc = {0, 0, nSurfaceWidth, nSurfaceHeight};
	AdjustWindowRect(&rc, dwStyle, FALSE);
	int nAdjustWidth = rc.right - rc.left;
	int nAdjustHeight = rc.bottom - rc.top;

	// create the window
	HWND hWindow = CreateWindow(
		ConfigUtil::GetInstance().GetString("WINDOW_CLASS"),
		ConfigUtil::GetInstance().GetString("WINDOW_TITLE"),
		dwStyle,
		(nScreenWidth-nAdjustWidth)/2,
		(nScreenHeight-nAdjustHeight)/2,
		nAdjustWidth,
		nAdjustHeight,
		NULL, NULL, hInstance, NULL);

	ShowWindow(hWindow, SW_SHOW);
	SetForegroundWindow(hWindow);
	SetFocus(hWindow);

	return hWindow;
}

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
	ConfigUtil::GetInstance().AddString("WINDOW_CLASS", "SPANK");
	ConfigUtil::GetInstance().AddString("WINDOW_TITLE", "spank");
	ConfigUtil::GetInstance().AddString("RESOURCE_DIR", "..\\..\\resources\\");
	ConfigUtil::GetInstance().AddInt("SURFACE_WIDTH", WindowConfig::SURFACE_WIDTH);
	ConfigUtil::GetInstance().AddInt("SURFACE_HEIGHT", WindowConfig::SURFACE_HEIGHT);

	HWND hWindow = CreateMainWindow();
	if (!hWindow) return 0;

	ConfigUtil::GetInstance().AddPointer("NATIVE_WINDOW", hWindow);

	bool bOK = ICore::GetInstance().Initialize();
	if (bOK) EnterMessageLoop();
	ICore::GetInstance().Terminate();

	DestroyMainWindow(hWindow);

	return 0;
}
