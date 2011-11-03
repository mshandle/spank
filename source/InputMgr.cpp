/*!
 * \file InputMgr.cpp
 * \date 8-10-2011 14:19:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <InputMgr.h>
#include <util/IDebugUtil.h>
#include <msg/MsgMgr.h>
#include <msg/MsgTouch.h>
#include <msg/MsgKey.h>

InputMgr& InputMgr::GetInstance()
{
	static InputMgr s_InputMgr;
	return s_InputMgr;
}

InputMgr::InputMgr()
{
	memset(m_bTouchDown, 0, sizeof(m_bTouchDown));
}

InputMgr::~InputMgr()
{
	// TODO: 
}

bool InputMgr::Initialize()
{
	memset(m_bTouchDown, 0, sizeof(m_bTouchDown));
	return true;
}

void InputMgr::Terminate()
{
	// TODO: 
}

void InputMgr::OnTouchStart(int nIndex, float x, float y)
{
	if (nIndex < 0 || nIndex >= MAX_TOUCH_SUPPORT) return;
	m_bTouchDown[nIndex] = true;

	// send message to notify input event
	MsgTouch* pMsgTouchEvent = new MsgTouch(MsgTouch::TT_BEGIN, 0, x, y);
	MsgMgr::GetInstance().SendMessage(pMsgTouchEvent);
}

void InputMgr::OnTouchMove(int nIndex, float x, float y)
{
	if (nIndex < 0 || nIndex >= MAX_TOUCH_SUPPORT) return;
	if (!m_bTouchDown[nIndex]) return;

	// send message to notify input event
	MsgTouch* pMsgTouchEvent = new MsgTouch(MsgTouch::TT_MOVE, 0, x, y);
	MsgMgr::GetInstance().SendMessage(pMsgTouchEvent);
}

void InputMgr::OnTouchEnd(int nIndex, float x, float y)
{
	if (nIndex < 0 || nIndex >= MAX_TOUCH_SUPPORT) return;
	m_bTouchDown[nIndex] = false;
	// send message to notify input event
	MsgTouch* pMsgTouchEvent = new MsgTouch(MsgTouch::TT_END, 0, x, y);
	MsgMgr::GetInstance().SendMessage(pMsgTouchEvent);
}

void InputMgr::OnKeyHome()
{
	MsgKey* pMsgKeyEvent = new MsgKey(MsgKey::KT_HOME);
	MsgMgr::GetInstance().SendMessage(pMsgKeyEvent);
}

void InputMgr::OnKeyReturn()
{
	MsgKey* pMsgKeyEvent = new MsgKey(MsgKey::KT_RETURN);
	MsgMgr::GetInstance().SendMessage(pMsgKeyEvent);
}
