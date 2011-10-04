/*!
 * \file ActionQuintMoveTo.h
 * \date 2011/09/16 17:53
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONQUINTMOVETO_H
#define __ACTIONQUINTMOVETO_H

#include "IActionBase.h"
#include "ActionMoveTo.h"

class ActionQuintMoveTo :public ActionMoveTo
{
public:
	DECLARE_RTTI(ActionQuintMoveTo, ActionMoveTo);
public:
	ActionQuintMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionQuintMoveTo();

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();

protected:
	virtual float Interpolate();
private:
	ACTION_TWEEN_TYPE m_eType;
};
#endif//__ACTIONQUINTMOVETO_H