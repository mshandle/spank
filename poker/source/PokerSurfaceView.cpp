/*!
 * \file PokerSurfaceView.cpp
 * \date 11-22-2011 10:00:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PokerSurfaceView.h"
#include <util/IDebugUtil.h>
#include <msg/MsgMgr.h>
#include <msg/MsgTouch.h>
#include <msg/MsgID.h>

PokerSurfaceView::PokerSurfaceView()
{
	// TODO: 
}

PokerSurfaceView::~PokerSurfaceView()
{
	// TODO: 
}

bool PokerSurfaceView::Initialize()
{
	MsgMgr::GetInstance().SubscribeMessage(MI_TOUCH, this, (MSG_CALLBACK)&PokerSurfaceView::OnMsgTouch);

	return true;
}

void PokerSurfaceView::Terminate()
{
	MsgMgr::GetInstance().UnsubscribeMessage(MI_TOUCH, this);
}

void PokerSurfaceView::Update(float dt)
{
	// TODO: 
}

void PokerSurfaceView::Render()
{
	// TODO: 
}

bool PokerSurfaceView::OnMsgTouch(IMsgBase* pMsg)
{
	MsgTouch* pMsgTouch = (MsgTouch*)pMsg;

	if (pMsgTouch->IsTouchBegin())
	{
		LOGD("touch begin: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
// 		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_BEGIN);
	}
	else if (pMsgTouch->IsTouchMove())
	{
		LOGD("touch move: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
// 		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_MOVE);
	}
	else if (pMsgTouch->IsTouchEnd())
	{
		LOGD("touch end: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
// 		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_END);
	}

	return true;
}
