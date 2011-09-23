/*!
 * \file ActionCompose.h
 * \date 8-17-2011 13:53:49
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ACTIONCOMPOSE_H__
#define __ACTIONCOMPOSE_H__

#include "IActionBase.h"
#include "../msg/IMsgBase.h"
#include <vector>

class ActionCompose : public IActionBase
{
public:
	typedef std::vector<IActionBase*> TV_ACTION_BASE;

public:
	DECLARE_RTTI(ActionCompose, IActionBase);

	ActionCompose();
	virtual ~ActionCompose();

	IActionBase* AddAction(IActionBase* pAction);
	IActionBase* GetAction(int nIndex);

	virtual void Reset();
	virtual void Update(float dt);

	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;

private:
	bool OnActionUpdate(IMsgBase* pMsg);

private:
	TV_ACTION_BASE m_vAction;

	float m_fCurrTime;
	float m_fMaxTime;

};
#endif // __ACTIONCOMPOSE_H__
