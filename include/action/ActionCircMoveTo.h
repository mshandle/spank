/*!
 * \file ActionCircMoveTo
 * \date 2011/9/17 17:24
 *
 *
 * \author wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __ACTIONCIRCMOVETO_H_
#define __ACTIONCIRCMOVETO_H_

#include "IActionBase.h"
#include "action/ActionMoveTo.h"

class ActionCircMoveTo : public ActionMoveTo
{
public:
	DECLARE_RTTI(ActionCircMoveTo, ActionMoveTo);
public:
	ActionCircMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionCircMoveTo();

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();
protected:
	virtual float Interpolate();
private:
	ACTION_TWEEN_TYPE m_eType;

};
#endif//__ACTIONCIRCMOVETO_H_