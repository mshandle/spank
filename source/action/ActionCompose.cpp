/*!
 * \file ActionCompose.cpp
 * \date 8-17-2011 13:53:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <action/ActionCompose.h>
#include <msg/MsgID.h>
#include <msg/MsgActionUpdate.h>

ActionCompose::ActionCompose()
{
	m_fMaxTime = 0.0f;
	Reset();
}

ActionCompose::~ActionCompose()
{
	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		SAFE_RELEASE(pAction);
	}
	m_vAction.clear();
}

IActionBase* ActionCompose::AddAction(IActionBase* pAction)
{
	if (!pAction) return NULL;

	pAction->ConnectEvent(MI_ACTION_UPDATE, this, (MSG_CALLBACK)&ActionCompose::OnActionUpdate);
	if (m_fMaxTime < pAction->GetTimeLength()) m_fMaxTime = pAction->GetTimeLength();
	m_vAction.push_back(pAction);
	return pAction;
}

IActionBase* ActionCompose::GetAction(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_vAction.size()) return NULL;
	return m_vAction[nIndex];
}

void ActionCompose::Reset()
{
	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		pAction->Reset();
	}
	m_fCurrTime = 0.0f;
}

void ActionCompose::Update(float dt)
{
	if (!IsRunning()) return;

	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		if (!pAction->IsRunning()) pAction->Start();
		pAction->Update(dt);
	}

	m_fCurrTime += dt;
	if (m_fCurrTime > m_fMaxTime)
	{
		Stop();
	}
}

IActionBase* ActionCompose::Clone()
{
	ActionCompose* pActionCompose = new ActionCompose();
	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		pActionCompose->AddAction(pAction->Clone());
	}

	return pActionCompose;
}

IActionBase* ActionCompose::CloneInverse()
{
	ActionCompose* pActionCompose = new ActionCompose();
	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		pActionCompose->AddAction(pAction->CloneInverse());
	}

	return pActionCompose;
}

float ActionCompose::GetTimeLength() const
{
	return m_fMaxTime;
}

bool ActionCompose::OnActionUpdate(IMsgBase* pMsg)
{
	MsgActionUpdate* pMsgActionUpdate = (MsgActionUpdate*)pMsg;
	switch (pMsgActionUpdate->GetUpdateType())
	{
	case AUT_SCALE:
		{
			SetScale(pMsgActionUpdate->GetScale());
		}
		break;
	case AUT_POSITION:
		{
			SetPosition(pMsgActionUpdate->GetPosition());
		}
		break;
	case AUT_ROTATION:
		{
			SetRotation(pMsgActionUpdate->GetRotation());
		}
		break;
	case AUT_START:
		{
			// notify sub action started
			NotifySubActionUpdate(AUT_SUBACTION_START, pMsgActionUpdate->GetAction());
		}
		break;
	case AUT_PAUSE:
		{
			// notify sub action paused
			NotifySubActionUpdate(AUT_SUBACTION_PAUSE, pMsgActionUpdate->GetAction());
		}
		break;
	case AUT_STOPED:
		{
			// notify sub action stoped
			NotifySubActionUpdate(AUT_SUBACTION_STOPED, pMsgActionUpdate->GetAction());
		}
		break;
	}

	return true;
}

void ActionCompose::NotifySubActionUpdate(ACTION_UPDATE_TYPE eType, IActionBase* pAction)
{
	MsgActionUpdate msg(eType, pAction);
	CallEvent(msg);
}
