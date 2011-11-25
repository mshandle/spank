/*!
 * \file OSUISystem_Mac_Impl.mm
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#import "OSUISystem_Mac_Impl.h"
#import "SpankAppDelegate.h"

IOSUISystem& IOSUISystem::GetInstance()
{
	static OSUISystem_Mac_Impl s_OSUISystem_Mac_Impl;
	return s_OSUISystem_Mac_Impl;
}

OSUISystem_Mac_Impl::OSUISystem_Mac_Impl()
{
	// TODO: 
}

OSUISystem_Mac_Impl::~OSUISystem_Mac_Impl()
{
	// TODO: 
}

bool OSUISystem_Mac_Impl::Initialize()
{
	return true;
}

void OSUISystem_Mac_Impl::Terminate()
{
	// TODO: 
}

int OSUISystem_Mac_Impl::CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height, const char* pszText)
{
	int nViewId = pSurfaceView->GetViewId();
	return [[SpankAppDelegate GetInstance] createButton:nViewId x:x y:y width:width height:height text:pszText];
}

int OSUISystem_Mac_Impl::CreateEditText(ISurfaceView* pSurfaceView, int x, int y, int width, int height)
{
	int nViewId = pSurfaceView->GetViewId();
	return [[SpankAppDelegate GetInstance] createEditText:nViewId x:x y:y width:width height:height];
}

void OSUISystem_Mac_Impl::DestroyControl(ISurfaceView* pSurfaceView, int nId)
{
	int nViewId = pSurfaceView->GetViewId();
	[[SpankAppDelegate GetInstance] destroyButton:nViewId buttonId:nId];
}
