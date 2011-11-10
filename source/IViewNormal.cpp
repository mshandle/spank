/*!
 * \file IViewNormal.cpp
 * \date 11-08-2011 10:26:36
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IViewNormal.h>
#include <ISurfaceViewMgr.h>

IViewNormal::IViewNormal()
{
	m_pSurfaceView = NULL;
	m_bOK = Create();
}

IViewNormal::IViewNormal(ISurfaceView* pSurfaceView)
{
	m_pSurfaceView = pSurfaceView;
	m_bOK = true;
}

IViewNormal::~IViewNormal()
{
	SAFE_RELEASE(m_pSurfaceView);
}

bool IViewNormal::Create()
{
	m_pSurfaceView = ISurfaceViewMgr::GetInstance().CreateSurfaceViewNormal();
	if (!m_pSurfaceView) return false;
	return true;
}

bool IViewNormal::OnAttachWindow()
{
	if (!m_pSurfaceView) return false;
	if (!m_pSurfaceView->ActiveView()) return false;
	return Initialize();
}

bool IViewNormal::OnDettachWindow()
{
	Terminate();
	if (!m_pSurfaceView) return false;
	m_pSurfaceView->DeactiveView();
	return true;
}

ISurfaceView* IViewNormal::GetSurfaceView() const
{
	return m_pSurfaceView;
}
