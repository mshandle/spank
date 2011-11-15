/*!
 * \file NetworkTestCase.h
 * \date 11-15-2011 10:57:12
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NETWORKTESTCASE_H__
#define __NETWORKTESTCASE_H__

#include "TestCase.h"
#include "PokerMsgHandler.h"

class NetworkTestCase : public TestCase
{
public:
	DECLARE_RTTI(NetworkTestCase, TestCase);

	NetworkTestCase();
	virtual ~NetworkTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	bool OnBtnConnectClicked(IMsgBase* pMsg);
	bool OnBtnSendClicked(IMsgBase* pMsg);
	bool OnBtnDisconnectClicked(IMsgBase* pMsg);

	bool OnMsgLoginServerValidate(short nType, StreamReader* pReader);

private:
	PokerMsgHandler m_Handler;

};
#endif // __NETWORKTESTCASE_H__
