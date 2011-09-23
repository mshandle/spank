/*!
 * \file ActionLoop.h
 * \date 8-17-2011 11:33:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ACTIONLOOP_H__
#define __ACTIONLOOP_H__

#include "IActionBase.h"

class ActionLoop : public IActionBase
{
public:
	DECLARE_RTTI(ActionLoop, IActionBase);

	ActionLoop(IActionBase* pAction, int nLoop = 0);
	virtual ~ActionLoop();

	void SetLoop(int nLoop);
	int GetLoop() const;
	int GetCurrentLoop() const;

	virtual void Reset();
	virtual void Update(float dt);

	virtual IActionBase* Clone();
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;

private:
	bool OnActionUpdate(IMsgBase* pMsg);

private:
	IActionBase* m_pAction;
	int m_nLoop;
	int m_nCurrLoop;
};
#endif // __ACTIONLOOP_H__
