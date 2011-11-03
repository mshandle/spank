/*!
 * \file SurfaceView_Win32_Gdi_Impl.h
 * \date 11-02-2011 14:09:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SURFACEVIEW_WIN32_GDI_IMPL_H__
#define __SURFACEVIEW_WIN32_GDI_IMPL_H__

#include <ISurfaceView.h>
#include <windows.h>

class SurfaceView_Win32_Gdi_Impl : public ISurfaceView
{
public:
	DECLARE_RTTI(SurfaceView_Win32_Gdi_Impl, ISurfaceView);

	SurfaceView_Win32_Gdi_Impl();
	virtual ~SurfaceView_Win32_Gdi_Impl();

	virtual int GetSurfaceWidth() const;
	virtual int GetSurfaceHeight() const;

	virtual bool ActiveView();
	virtual void DeactiveView();

	virtual void BeginRender();
	virtual void EndRender();

private:
	bool CreateView();
	void DestroyView();
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

private:
	HWND m_hWindow;
	int m_nSurfaceWidth;
	int m_nSurfaceHeight;

};
#endif // __SURFACEVIEW_WIN32_GDI_IMPL_H__
