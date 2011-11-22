/*!
 * \file PokerGameApp.cpp
 * \date 11-22-2011 9:55:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PokerGameApp.h"
#include <ICore.h>
#include <msg/MsgMgr.h>

IGameApp& IGameApp::GetInstance()
{
	static PokerGameApp s_PokerGameApp;
	return s_PokerGameApp;
}

PokerGameApp::PokerGameApp()
{
	// TODO: 
}

PokerGameApp::~PokerGameApp()
{
	// TODO: 
}

bool PokerGameApp::Initialize()
{
	m_pSurfaceView = new PokerSurfaceView();
	ICore::GetInstance().SetCurrentView(m_pSurfaceView);
	return true;
}

void PokerGameApp::Terminate()
{
	SAFE_RELEASE(m_pSurfaceView);
}
