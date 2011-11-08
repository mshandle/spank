/*!
 * \file GameApp.cpp
 * \date 7-21-2011 14:42:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameApp.h"
#include "NormalView.h"
#include "OpenGLView.h"
#include <msg/MsgMgr.h>
#include <msg/MsgID.h>
#include <msg/MsgKey.h>
#include <util/IDebugUtil.h>
#include <ICore.h>

IGameApp& IGameApp::GetInstance()
{
	static GameApp s_GameApp;
	return s_GameApp;
}

GameApp::GameApp()
{
	memset(m_pView, 0, sizeof(m_pView));
}

GameApp::~GameApp()
{
	// TODO: 
}

bool GameApp::Initialize()
{
	MsgMgr::GetInstance().SubscribeMessage(MI_KEY, this, (MSG_CALLBACK)&GameApp::OnMsgKey);

	m_pView[0] = new NormalView();
	m_pView[1] = new OpenGLView();
	m_nIndex = 0;

	ICore::GetInstance().SetCurrentView(m_pView[m_nIndex]);

	return true;
}

void GameApp::Terminate()
{
	SAFE_DELETE(m_pView[0]);
	SAFE_DELETE(m_pView[1]);
}

bool GameApp::OnMsgKey(IMsgBase* pMsg)
{
	MsgKey* pMsgKey = (MsgKey*)pMsg;
	if (pMsgKey->IsHome())
	{
		LOGD("on key home");
		ICore::GetInstance().End();
	}
	else if (pMsgKey->IsReturn())
	{
		LOGD("on key return");
		m_nIndex = (m_nIndex + 1) % 2;
		ICore::GetInstance().SetCurrentView(m_pView[m_nIndex]);
	}

	return true;
}
