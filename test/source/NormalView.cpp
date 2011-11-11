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
	m_pButton = NULL;
}

NormalView::~NormalView()
{
	// TODO: 
}

bool NormalView::Initialize()
{
//	m_pButton = IOSUISystem::GetInstance().CreateButton(GetSurfaceView(), 100, 100, 100, 30);
//	if (!m_pButton) return false;

	return true;
}

void NormalView::Terminate()
{
	IOSUISystem::GetInstance().DestroyButton(m_pButton);
	m_pButton = NULL;
}

void NormalView::Update(float dt)
{
	// TODO: 
}
