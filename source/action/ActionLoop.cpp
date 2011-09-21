/*!
 * \file ActionLoop.cpp
 * \date 8-17-2011 11:33:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <action/ActionLoop.h>
#include <msg/MsgID.h>
#include <msg/MsgActionUpdate.h>

ActionLoop::ActionLoop(IActionBase* pAction, int nLoop /* = 0 */)
{
	m_pAction = pAction;
	m_pAction->ConnectEvent(MI_ACTION_UPDATE, this, (MSG_CALLBACK)&ActionLoop::OnActionUpdate);
	m_nLoop = nLoop;

	Reset();
}

ActionLoop::~ActionLoop()
{
	SAFE_RELEASE(m_pAction);
}

void ActionLoop::SetLoop(int nLoop)
{
	m_nLoop = nLoop;
}

int ActionLoop::GetLoop() const
{
	return m_nLoop;
}

int ActionLoop::GetCurrentLoop() const
{
	return m_nCurrLoop;
}

void ActionLoop::Reset()
{
	m_nCurrLoop = m_nLoop;
}

void ActionLoop::Update(float dt)
{
	if (!IsRunning()) return;

	if (!m_pAction->IsRunning())
	{
		m_pAction->Start();
		if (m_nCurrLoop > 0) --m_nCurrLoop;
	}

	m_pAction->Update(dt);
}

IActionBase* ActionLoop::Clone()
{
	return new ActionLoop(m_pAction->Clone(), m_nLoop);
}

IActionBase* ActionLoop::CloneInverse()
{
	return new ActionLoop(m_pAction->CloneInverse(), m_nLoop);
}

float ActionLoop::GetTimeLength() const
{
	if (m_nLoop == 0) return IMath::FLOAT_MAX;
	return m_nLoop*m_pAction->GetTimeLength();
}

bool ActionLoop::OnActionUpdate(IMsgBase* pMsg)
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

			if (m_nLoop > 0 && m_nCurrLoop == 0)
			{
				Stop();
			}
		}
		break;
	}

	return true;
}

void ActionLoop::NotifySubActionUpdate(ACTION_UPDATE_TYPE eType, IActionBase* pAction)
{
	MsgActionUpdate msg(eType, pAction);
	CallEvent(msg);
}
