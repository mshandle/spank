/*!
 * \file Core_Impl.cpp
 * \date 7-25-2011 10:13:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Core_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>
#include <util/IFileUtil.h>
#include <msg/MsgMgr.h>
#include <util/ScreenUtil.h>
#include <InputMgr.h>
#include <ISurfaceViewMgr.h>
#include <IGameApp.h>
#include <IViewOpenGL.h>

ICore& ICore::GetInstance()
{
	static Core_Impl s_Core_Impl;
	return s_Core_Impl;
}

Core_Impl::Core_Impl()
{
	m_pCurrentView = NULL;
	m_bRunning = false;
}

Core_Impl::~Core_Impl()
{
	// TODO: 
}

bool Core_Impl::Initialize()
{
	// initialize common utilities
	if (!ConfigUtil::GetInstance().Initialize()) return false;
	if (!IDebugUtil::GetInstance().Initialize()) return false;
	if (!IFileUtil::GetInstance().Initialize()) return false;
	if (!MsgMgr::GetInstance().Initialize()) return false;
	if (!ScreenUtil::GetInstance().Initialize()) return false;
	if (!InputMgr::GetInstance().Initialize()) return false;
	if (!ISurfaceViewMgr::GetInstance().Initialize()) return false;
	if (!IGameApp::GetInstance().Initialize()) return false;

	m_bRunning = true;
	return true;
}

void Core_Impl::Terminate()
{
	IGameApp::GetInstance().Terminate();
	ISurfaceViewMgr::GetInstance().Terminate();
	InputMgr::GetInstance().Terminate();
	ScreenUtil::GetInstance().Terminate();
	MsgMgr::GetInstance().Terminate();
	IFileUtil::GetInstance().Terminate();
	IDebugUtil::GetInstance().Terminate();
	ConfigUtil::GetInstance().Terminate();
}

bool Core_Impl::SetCurrentView(IViewNormal* pView)
{
	if (m_pCurrentView == pView) return true;

	// dettach current view
	if (m_pCurrentView)
	{
		if (!m_pCurrentView->OnDettachWindow())
		{
			LOGE("detach view from window failed");
			m_pCurrentView = NULL;
			return false;
		}
	}
	m_pCurrentView = NULL;

	// attach new view
	if (pView)
	{
		if (!pView->OnAttachWindow())
		{
			pView->OnDettachWindow();
			LOGE("attach to window failed");
			return false;
		}
		m_pCurrentView = pView;
	}

	return true;
}

IViewNormal* Core_Impl::GetCurrentView()
{
	return m_pCurrentView;
}

void Core_Impl::Update(float dt)
{
	MsgMgr::GetInstance().DispatchMessage();

	if (m_pCurrentView) m_pCurrentView->Update(dt);
}

void Core_Impl::Render()
{
	if (m_pCurrentView && m_pCurrentView->GetRtti()->IsDerived(IViewOpenGL::__RttiData()))
	{
		IViewOpenGL* pView = (IViewOpenGL*) m_pCurrentView;

		pView->BeginRender();
		pView->Render();
		pView->EndRender();
	}
}

void Core_Impl::End()
{
	m_bRunning = false;
}

bool Core_Impl::IsRunning() const
{
	return m_bRunning;
}
