/*!
 * \file SurfaceView_Win32_Gdi_Impl.cpp
 * \date 11-02-2011 14:10:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceView_Win32_Gdi_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <InputMgr.h>
#include <math/IMath.h>

SurfaceView_Win32_Gdi_Impl::SurfaceView_Win32_Gdi_Impl()
{
	m_hWindow = NULL;
	m_nSurfaceWidth = 0;
	m_nSurfaceHeight = 0;

	m_bOK = CreateView();
}

SurfaceView_Win32_Gdi_Impl::~SurfaceView_Win32_Gdi_Impl()
{
	DestroyView();

	m_hWindow = NULL;
	m_nSurfaceWidth = 0;
	m_nSurfaceHeight = 0;
}

int SurfaceView_Win32_Gdi_Impl::GetSurfaceWidth() const
{
	return m_nSurfaceWidth;
}

int SurfaceView_Win32_Gdi_Impl::GetSurfaceHeight() const
{
	return m_nSurfaceHeight;
}

bool SurfaceView_Win32_Gdi_Impl::ActiveView()
{
	if (!m_hWindow) return false;

	ShowWindow(m_hWindow, SW_SHOW);
	SetForegroundWindow(m_hWindow);
	SetFocus(m_hWindow);

	return true;
}

void SurfaceView_Win32_Gdi_Impl::DeactiveView()
{
	if (m_hWindow) ShowWindow(m_hWindow, SW_HIDE);
}

void SurfaceView_Win32_Gdi_Impl::BeginRender()
{
	// TODO: 
}

void SurfaceView_Win32_Gdi_Impl::EndRender()
{
	// TODO: 
}

bool SurfaceView_Win32_Gdi_Impl::CreateView()
{
	m_nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	m_nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (m_nSurfaceWidth <= 0 || m_nSurfaceHeight <= 0) return false;

	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS winClass;
	memset(&winClass, 0, sizeof(winClass));
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.lpfnWndProc = (WNDPROC)SurfaceView_Win32_Gdi_Impl::MainWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = ConfigUtil::GetInstance().GetString("WINDOW_CLASS_GDI");
	RegisterClass(&winClass);

	// screen width, height
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// window width, height
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	RECT rc = {0, 0, m_nSurfaceWidth, m_nSurfaceHeight};
	AdjustWindowRect(&rc, dwStyle, FALSE);
	int nAdjustWidth = rc.right - rc.left;
	int nAdjustHeight = rc.bottom - rc.top;

	// create the window
	m_hWindow = CreateWindow(
		ConfigUtil::GetInstance().GetString("WINDOW_CLASS_GDI"),
		ConfigUtil::GetInstance().GetString("WINDOW_TITLE"),
		dwStyle,
		(nScreenWidth-nAdjustWidth)/2,
		(nScreenHeight-nAdjustHeight)/2,
		nAdjustWidth,
		nAdjustHeight,
		NULL, NULL, hInstance, NULL);

	LOGD("window initialized");
	return true;
}

void SurfaceView_Win32_Gdi_Impl::DestroyView()
{
	if (m_hWindow)
	{
		DestroyWindow(m_hWindow);
		m_hWindow = NULL;
	}
	LOGD("window terminated");
}

LRESULT CALLBACK SurfaceView_Win32_Gdi_Impl::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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
	case WM_DESTROY:
		{
			PostQuitMessage(0);
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
