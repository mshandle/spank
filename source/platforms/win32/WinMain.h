/*!
 * \file WinMain.h
 * \date 7-21-2011 11:55:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __WINMAIN_H__
#define __WINMAIN_H__

class WindowConfig
{
public:
	enum CONST_DEFINE
	{
		SURFACE_WIDTH = 1280,
		SURFACE_HEIGHT = 720,
		WM_SOCKET = 0x0400 + 1,		// WM_USER + 1
	};
};
#endif // __WINMAIN_H__
