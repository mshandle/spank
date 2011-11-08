/*!
 * \file IViewOpenGL.cpp
 * \date 11-08-2011 10:37:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IViewOpenGL.h>
#include <ISurfaceViewMgr.h>
#include <ITextureMgr.h>
#include <IResourceMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <ui/IUISystem.h>

IViewOpenGL::IViewOpenGL()
:IViewNormal(NULL)
{
	m_pSurfaceView = NULL;
	m_bOK = Create();
}

IViewOpenGL::~IViewOpenGL()
{
	// TODO: 
}

bool IViewOpenGL::OnAttachWindow()
{
	if (!m_pSurfaceView) return false;
	if (!m_pSurfaceView->ActiveView()) return false;
	// initialize singleton
	if (!ITextureMgr::GetInstance().Initialize()) return false;
	if (!IResourceMgr::GetInstance().Initialize()) return false;
	if (!IShaderMgr::GetInstance().Initialize()) return false;
	if (!IRenderer2D::GetInstance().Initialize()) return false;
	if (!IRendererUI::GetInstance().Initialize()) return false;
	if (!IUIResMgr::GetInstance().Initialize()) return false;
	if (!IUISystem::GetInstance().Initialize()) return false;
	return Initialize();
}

bool IViewOpenGL::OnDettachWindow()
{
	Terminate();
	// terminate singleton
	IUISystem::GetInstance().Terminate();
	IUIResMgr::GetInstance().Terminate();
	IRendererUI::GetInstance().Terminate();
	IRenderer2D::GetInstance().Terminate();
	IShaderMgr::GetInstance().Terminate();
	IResourceMgr::GetInstance().Terminate();
	ITextureMgr::GetInstance().Terminate();
	m_pSurfaceView->DeactiveView();
	return true;
}

void IViewOpenGL::BeginRender()
{
	if (m_pSurfaceView) m_pSurfaceView->BeginRender();
}

void IViewOpenGL::EndRender()
{
	if (m_pSurfaceView) m_pSurfaceView->EndRender();
}

bool IViewOpenGL::Create()
{
	m_pSurfaceView = ISurfaceViewMgr::GetInstance().CreateSurfaceViewOpenGL();
	if (!m_pSurfaceView) return false;
	return true;
}
