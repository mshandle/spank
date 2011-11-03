/*!
 * \file SurfaceView_Win32_Ogl_Impl.cpp
 * \date 11-02-2011 14:13:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SurfaceView_Win32_Ogl_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <InputMgr.h>
#include <math/IMath.h>
#include <GLES2/gl2.h>

SurfaceView_Win32_Ogl_Impl::SurfaceView_Win32_Ogl_Impl()
{
	m_EGLDisplay = NULL;
	m_EGLSurface = NULL;
	m_EGLContext = NULL;
	m_hWindow = NULL;
	m_nSurfaceWidth = 0;
	m_nSurfaceHeight = 0;

	m_bOK = CreateView();
}

SurfaceView_Win32_Ogl_Impl::~SurfaceView_Win32_Ogl_Impl()
{
	DestroyView();
}

int SurfaceView_Win32_Ogl_Impl::GetSurfaceWidth() const
{
	return m_nSurfaceWidth;
}

int SurfaceView_Win32_Ogl_Impl::GetSurfaceHeight() const
{
	return m_nSurfaceHeight;
}

bool SurfaceView_Win32_Ogl_Impl::ActiveView()
{
	if (!m_hWindow) return false;

	// show window
	ShowWindow(m_hWindow, SW_SHOW);
	SetForegroundWindow(m_hWindow);
	SetFocus(m_hWindow);

	// bind opengl es to window
	if (!InitializeEGL(m_hWindow)) return false;

	// set view port
	glViewport(0, 0, m_nSurfaceWidth, m_nSurfaceHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	return true;
}

void SurfaceView_Win32_Ogl_Impl::DeactiveView()
{
	if (m_hWindow) ShowWindow(m_hWindow, SW_HIDE);
	TerminateEGL();
}

void SurfaceView_Win32_Ogl_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glClearColor error code: 0x%04x", eError);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glClear error code: 0x%04x", eError);
}

void SurfaceView_Win32_Ogl_Impl::EndRender()
{
	glFlush();
	GLenum eError = glGetError();
	if (eError != GL_NO_ERROR) LOGE("glFlush error code: 0x%04x", eError);

	eglSwapBuffers(m_EGLDisplay, m_EGLSurface);
}

bool SurfaceView_Win32_Ogl_Impl::CreateView()
{
	m_nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	m_nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (m_nSurfaceWidth <= 0 || m_nSurfaceHeight <= 0) return false;

	return InitializeWindow();
}

void SurfaceView_Win32_Ogl_Impl::DestroyView()
{
	DeactiveView();
	TerminateWindow();
}

bool SurfaceView_Win32_Ogl_Impl::InitializeWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS winClass;
	memset(&winClass, 0, sizeof(winClass));
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC)SurfaceView_Win32_Ogl_Impl::MainWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = NULL;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = ConfigUtil::GetInstance().GetString("WINDOW_CLASS_OGL");
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
		ConfigUtil::GetInstance().GetString("WINDOW_CLASS_OGL"),
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

void SurfaceView_Win32_Ogl_Impl::TerminateWindow()
{
	if (m_hWindow)
	{
		DestroyWindow(m_hWindow);
		m_hWindow = NULL;
	}
	LOGD("window terminated");
}

LRESULT CALLBACK SurfaceView_Win32_Ogl_Impl::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

bool SurfaceView_Win32_Ogl_Impl::InitializeEGL(HWND hWindow)
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

	if (IsEGLInitialized()) return true;

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

void SurfaceView_Win32_Ogl_Impl::TerminateEGL()
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

bool SurfaceView_Win32_Ogl_Impl::IsEGLInitialized()
{
	return (m_EGLDisplay != NULL);
}
