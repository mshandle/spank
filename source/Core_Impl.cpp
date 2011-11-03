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
#include <ITextureMgr.h>
#include <IResourceMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <ui/IUISystem.h>
#include <IGameApp.h>
#include "Node_Impl.h"

ICore& ICore::GetInstance()
{
	static Core_Impl s_Core_Impl;
	return s_Core_Impl;
}

Core_Impl::Core_Impl()
{
	m_pRootNode = NULL;
	m_pSurfaceView = NULL;
	m_bRunning = false;
}

Core_Impl::~Core_Impl()
{
	// TODO: 
}

bool Core_Impl::PreInitialize()
{
	m_pRootNode = new Node_Impl();
	return true;
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

// 	// 
// 	if (!ITextureMgr::GetInstance().Initialize()) return false;
// 	if (!IResourceMgr::GetInstance().Initialize()) return false;
// 	if (!IShaderMgr::GetInstance().Initialize()) return false;
// 	if (!IRenderer2D::GetInstance().Initialize()) return false;
// 	if (!IRendererUI::GetInstance().Initialize()) return false;
// 	if (!IUIResMgr::GetInstance().Initialize()) return false;
// 	if (!IUISystem::GetInstance().Initialize()) return false;

	if (!PreInitialize()) return false;
	if (!IGameApp::GetInstance().Initialize()) return false;

	if (!PostInitialize()) return false;

	m_bRunning = true;
	return true;
}

bool Core_Impl::PostInitialize()
{
	m_pRootNode->UpdateMatrix(0.0f);
	return true;
}

void Core_Impl::PreTerminate()
{
	SAFE_DELETE(m_pRootNode);
}

void Core_Impl::Terminate()
{
	IGameApp::GetInstance().Terminate();
	PreTerminate();
// 	IUISystem::GetInstance().Terminate();
// 	IUIResMgr::GetInstance().Terminate();
// 	IRendererUI::GetInstance().Terminate();
// 	IRenderer2D::GetInstance().Terminate();
// 	IShaderMgr::GetInstance().Terminate();
// 	IResourceMgr::GetInstance().Terminate();
// 	ITextureMgr::GetInstance().Terminate();
// 	IRenderDevice::GetInstance().Terminate();

	// free common utilities
	InputMgr::GetInstance().Terminate();
	ScreenUtil::GetInstance().Terminate();
	MsgMgr::GetInstance().Terminate();
	IFileUtil::GetInstance().Terminate();
	IDebugUtil::GetInstance().Terminate();
	ConfigUtil::GetInstance().Terminate();

	PostTerminate();
}

void Core_Impl::PostTerminate()
{
	// nothing to do
}

bool Core_Impl::SetSurfaceView(ISurfaceView* pView)
{
	// free old view
	if (m_pSurfaceView != NULL)
	{
		m_pSurfaceView->DeactiveView();
	}

	// switch surface view
	m_pSurfaceView = pView;
	if (m_pSurfaceView) m_pSurfaceView->ActiveView();

	return true;
}

ISurfaceView* Core_Impl::GetSurfaceView()
{
	return m_pSurfaceView;
}

INode* Core_Impl::GetRootNode()
{
	return 	m_pRootNode;
}

void Core_Impl::PreUpdate(float dt)
{
	MsgMgr::GetInstance().DispatchMessage();
}

void Core_Impl::Update(float dt)
{
	PreUpdate(dt);

	IGameApp::GetInstance().Update(dt);
	IUISystem::GetInstance().Update(dt);

	PostUpdate(dt);
}

void Core_Impl::PostUpdate(float dt)
{
	// update actions
	m_pRootNode->UpdateAction(dt);

	// update objects
	m_pRootNode->UpdateObjects(dt);

	// update matrix
	m_pRootNode->UpdateMatrix(dt);
}

void Core_Impl::PreRender()
{
	// render system objects
	m_pRootNode->RenderObjects();
}

void Core_Impl::Render()
{
 	if (m_pSurfaceView) m_pSurfaceView->BeginRender();
// 	PreRender();
// 
// 	// render scene
// 	IRenderer2D::GetInstance().BeginRender();
// 	IGameApp::GetInstance().Render();
// 	IRenderer2D::GetInstance().EndRender();
// 
// 	// render ui
// 	IRendererUI::GetInstance().BeginRender();
// 	IUISystem::GetInstance().Render();
// 	IRendererUI::GetInstance().EndRender();
// 
// 	PostRender();
 	if (m_pSurfaceView) m_pSurfaceView->EndRender();
}

void Core_Impl::PostRender()
{
	// TODO: 
}

void Core_Impl::End()
{
	m_bRunning = false;
}

bool Core_Impl::IsRunning() const
{
	return m_bRunning;
}
