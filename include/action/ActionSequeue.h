/*!
 * \file ActionSequeue.h
 * \date 8-17-2011 10:37:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ACTIONSEQUEUE_H__
#define __ACTIONSEQUEUE_H__

#include "IActionBase.h"
#include "../msg/IMsgBase.h"
#include <vector>

class ActionSequeue : public IActionBase
{
public:
	typedef std::vector<IActionBase*> TV_ACTION_BASE;

public:
	DECLARE_RTTI(ActionSequeue, IActionBase);

	ActionSequeue();
	virtual ~ActionSequeue();

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
	int m_nCurrIndex;
	float m_fTimeLength;

};
#endif // __ACTIONSEQUEUE_H__
