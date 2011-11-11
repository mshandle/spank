/*!
 * \file OSUISystem_Mac_Impl.cpp
 * \date 11-10-2011
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "OSUISystem_Mac_Impl.h"

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

void* OSUISystem_Mac_Impl::CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height)
{
	// TODO: 
	return NULL;
}

void OSUISystem_Mac_Impl::DestroyButton(void* pHandler)
{
	// TODO: 
}
