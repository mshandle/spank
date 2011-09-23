/*!
 * \file ActionSequeue.cpp
 * \date 8-17-2011 10:37:12
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <action/ActionSequeue.h>
#include <msg/MsgID.h>
#include <msg/MsgActionUpdate.h>

ActionSequeue::ActionSequeue()
{
	m_fTimeLength = 0.0f;
	Reset();
}

ActionSequeue::~ActionSequeue()
{
	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		pAction->DisconnectEvent(MI_ACTION_UPDATE);
		SAFE_RELEASE(pAction);
	}
	m_vAction.clear();
}

IActionBase* ActionSequeue::AddAction(IActionBase* pAction)
{
	if (!pAction) return NULL;

	pAction->ConnectEvent(MI_ACTION_UPDATE, this, (MSG_CALLBACK)&ActionSequeue::OnActionUpdate);
	m_fTimeLength += pAction->GetTimeLength();
	m_vAction.push_back(pAction);
	return pAction;
}

IActionBase* ActionSequeue::GetAction(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_vAction.size()) return NULL;
	return m_vAction[nIndex];
}

void ActionSequeue::Reset()
{
	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		pAction->Reset();
	}
	m_nCurrIndex = 0;
}

void ActionSequeue::Update(float dt)
{
	if (!IsRunning()) return;

	IActionBase* pAction = GetAction(m_nCurrIndex);
	if (!pAction) return;

	if (!pAction->IsRunning()) pAction->Start();
	pAction->Update(dt);
}

IActionBase* ActionSequeue::Clone()
{
	ActionSequeue* pActionSequeue = new ActionSequeue();
	for (TV_ACTION_BASE::iterator it = m_vAction.begin(); it != m_vAction.end(); ++it)
	{
		IActionBase* pAction = (*it);
		pActionSequeue->AddAction(pAction->Clone());
	}

	return pActionSequeue;
}

IActionBase* ActionSequeue::CloneInverse()
{
	ActionSequeue* pActionSequeue = new ActionSequeue();
	for (TV_ACTION_BASE::reverse_iterator it = m_vAction.rbegin(); it != m_vAction.rend(); ++it)
	{
		IActionBase* pAction = (*it);
		pActionSequeue->AddAction(pAction->CloneInverse());
	}

	return pActionSequeue;
}

float ActionSequeue::GetTimeLength() const
{
	return m_fTimeLength;
}

bool ActionSequeue::OnActionUpdate(IMsgBase* pMsg)
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
	case AUT_STOPED:
		{
			if (!GetAction(++m_nCurrIndex))
			{
				Stop();
			}
		}
		break;
	}

	return true;
}
