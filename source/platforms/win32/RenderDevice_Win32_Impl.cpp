/*!
 * \file RenderDevice_Win32_Impl.cpp
 * \date 23-07-2011 10:33:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RenderDevice_Win32_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <InputMgr.h>
#include <GLES2/gl2.h>

IRenderDevice& IRenderDevice::GetInstance()
{
	static RenderDevice_Win32_Impl s_RenderDevice_Win32_Impl;
	return s_RenderDevice_Win32_Impl;
}

RenderDevice_Win32_Impl::RenderDevice_Win32_Impl()
{
	m_EGLDisplay = NULL;
	m_EGLSurface = NULL;
	m_EGLContext = NULL;
	m_hWindow = NULL;
	m_nSurfaceWidth = 0;
	m_nSurfaceHeight = 0;
}

RenderDevice_Win32_Impl::~RenderDevice_Win32_Impl()
{
	// TODO:
}

bool RenderDevice_Win32_Impl::Initialize()
{
	m_nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	m_nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (m_nSurfaceWidth <= 0 || m_nSurfaceHeight <= 0) return false;

	if (!InitializeWindow()) return false;
	if (!InitializeEGL(m_hWindow)) return false;

	// set view port
	glViewport(0, 0, m_nSurfaceWidth, m_nSurfaceHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
 	glCullFace(GL_FRONT);

	return true;
}

void RenderDevice_Win32_Impl::Terminate()
{
	TerminateEGL();
	TerminateWindow();
}

void RenderDevice_Win32_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glClearColor error code: 0x%04x", eError);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glClear error code: 0x%04x", eError);
}

void RenderDevice_Win32_Impl::EndRender()
{
	glFlush();
	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glFlush error code: 0x%04x", eError);

	eglSwapBuffers(m_EGLDisplay, m_EGLSurface);
}

bool RenderDevice_Win32_Impl::InitializeWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS winClass;
	memset(&winClass, 0, sizeof(winClass));
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC)RenderDevice_Win32_Impl::MainWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = NULL;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = ConfigUtil::GetInstance().GetString("WINDOW_CLASS");
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
		ConfigUtil::GetInstance().GetString("WINDOW_CLASS"),
		ConfigUtil::GetInstance().GetString("WINDOW_TITLE"),
		dwStyle,
		(nScreenWidth-nAdjustWidth)/2,
		(nScreenHeight-nAdjustHeight)/2,
		nAdjustWidth,
		nAdjustHeight,
		NULL, NULL, hInstance, NULL);

	ShowWindow(m_hWindow, SW_SHOW);
	SetForegroundWindow(m_hWindow);
	SetFocus(m_hWindow);

	LOGD("window initialized");
	return true;
}

void RenderDevice_Win32_Impl::TerminateWindow()
{
	if (m_hWindow)
	{
		DestroyWindow(m_hWindow);
		m_hWindow = NULL;
	}
	LOGD("window terminated");
}

LRESULT CALLBACK RenderDevice_Win32_Impl::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

bool RenderDevice_Win32_Impl::InitializeEGL(HWND hWindow)
{
	static const EGLint s_EGLAttributes[] =
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_ALPHA_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	static const EGLint s_EGLContextAttributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	HDC hDisplay = GetDC(NULL);
	if (!hDisplay) return false;

	m_EGLDisplay = eglGetDisplay(hDisplay);
	eglInitialize(m_EGLDisplay, NULL, NULL);

	EGLint numEGLConfigs = 0;
	EGLConfig eglConfigs[1] = {NULL};
	eglChooseConfig(m_EGLDisplay, s_EGLAttributes, eglConfigs, 1, &numEGLConfigs);

	m_EGLSurface = eglCreateWindowSurface(m_EGLDisplay, eglConfigs[0], (EGLNativeWindowType)hWindow, NULL);
	if (m_EGLSurface == EGL_NO_SURFACE) return false;

	m_EGLContext = eglCreateContext(m_EGLDisplay, eglConfigs[0], EGL_NO_CONTEXT, s_EGLContextAttributes);
	if (m_EGLContext == EGL_NO_CONTEXT) return false;

	eglMakeCurrent(m_EGLDisplay, m_EGLSurface, m_EGLSurface, m_EGLContext);

	LOGD("OpenGLES 2.0 initialized");
	return true;
}

void RenderDevice_Win32_Impl::TerminateEGL()
{
	if (m_EGLDisplay)
	{
		eglMakeCurrent(m_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroySurface(m_EGLDisplay, m_EGLSurface);
		eglDestroyContext(m_EGLDisplay, m_EGLContext);
		eglTerminate(m_EGLDisplay);
	}

	m_EGLDisplay = NULL;
	m_EGLSurface = NULL;
	m_EGLContext = NULL;

	LOGD("OpenGLES 2.0 terminated");
}

int RenderDevice_Win32_Impl::GetSurfaceWidth() const
{
	return m_nSurfaceWidth;
}

int RenderDevice_Win32_Impl::GetSurfaceHeight() const
{
	return m_nSurfaceHeight;
}
