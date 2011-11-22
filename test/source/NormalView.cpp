/*!
 * \file NormalView.cpp
 * \date 11-08-2011 11:20:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NormalView.h"
#include <osui/IOSUISystem.h>

NormalView::NormalView()
{
	// TODO: 
}

NormalView::~NormalView()
{
	// TODO: 
}

bool NormalView::Initialize()
{
	int nId = IOSUISystem::GetInstance().CreateButton(GetSurfaceView(), 100, 100, 100, 30, "Button1");
	nId = IOSUISystem::GetInstance().CreateButton(GetSurfaceView(), 100, 150, 100, 30, "Button2");
	IOSUISystem::GetInstance().DestroyControl(GetSurfaceView(), nId);
	nId = IOSUISystem::GetInstance().CreateButton(GetSurfaceView(), 100, 200, 100, 30, "Button3");
	nId = IOSUISystem::GetInstance().CreateButton(GetSurfaceView(), 100, 250, 100, 30, "Button4");
	IOSUISystem::GetInstance().DestroyControl(GetSurfaceView(), nId);
	nId = IOSUISystem::GetInstance().CreateButton(GetSurfaceView(), 100, 300, 100, 30, "Button5");

	IOSUISystem::GetInstance().CreateEditText(GetSurfaceView(), 100, 350, 100, 30);
	return true;
}

void NormalView::Terminate()
{
	// TODO: 
}

void NormalView::Update(float dt)
{
	// TODO: 
}
