/*!
 * \file NetworkTestCase.cpp
 * \date 11-15-2011 10:57:18
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NetworkTestCase.h"
#include <util/StringUtil.h>
#include <ui/UIButton.h>
#include <ui/uimsg/UIMsgID.h>
#include <net/INetMgr.h>
#include "poker_msgs/MsgClientLoginToLFor91.h"
#include "poker_msgs/MsgLoginServerValidate.h"

NetworkTestCase::NetworkTestCase()
:TestCase("Network")
{
	// TODO: 
}

NetworkTestCase::~NetworkTestCase()
{
	// TODO: 
}

bool NetworkTestCase::Initialize(UIScreen* pUIScreen)
{
	m_Handler.Reset();
	m_Handler.RegisterMessage(MsgLoginServerValidate::MSG_TYPE, this, (NET_MSG_CALLBACK)&NetworkTestCase::OnMsgLoginServerValidate);

	INetMgr::GetInstance().SetNetMsgHandler(&m_Handler);

	UIButton* pBtnConnect = new UIButton(pUIScreen, Vector2(10.0f, 10.0f), "Connect");
	pBtnConnect->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&NetworkTestCase::OnBtnConnectClicked);

	UIButton* pBtnSend = new UIButton(pUIScreen, Vector2(10.0f, 110.0f), "Send");
	pBtnSend->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&NetworkTestCase::OnBtnSendClicked);

	UIButton* pBtnDisconnect = new UIButton(pUIScreen, Vector2(10.0f, 210.0f), "Disconnect");
	pBtnDisconnect->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&NetworkTestCase::OnBtnDisconnectClicked);

	return true;
}

void NetworkTestCase::Terminate()
{
	INetMgr::GetInstance().Disconnect();
	INetMgr::GetInstance().SetNetMsgHandler(NULL);
	m_Handler.Reset();
}

void NetworkTestCase::Update(float dt)
{
	// TODO: 
}

void NetworkTestCase::Render()
{
	// TODO: 
}

bool NetworkTestCase::OnBtnConnectClicked(IMsgBase* pMsg)
{
	INetMgr::GetInstance().ConnectToServer("120.33.34.144", 5999);
	return true;
}

bool NetworkTestCase::OnBtnSendClicked(IMsgBase* pMsg)
{
	MsgClientLoginToLFor91 msg;
	StringUtil::CopyString(msg.uid, 52, "215501039");
	StringUtil::CopyString(msg.sessionId, 128, "2ddd4de7e9f04b6a8084050dcd544091");
	return INetMgr::GetInstance().SendNetMessage(&msg);
}

bool NetworkTestCase::OnBtnDisconnectClicked(IMsgBase* pMsg)
{
	INetMgr::GetInstance().Disconnect();
	return true;
}

bool NetworkTestCase::OnMsgLoginServerValidate(short nType, StreamReader* pReader)
{
	MsgLoginServerValidate msg;
	if (!msg.FromStream(pReader)) return false;

	return true;
}
