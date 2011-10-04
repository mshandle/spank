/*!
 * \file ActionQuartMoveTo.h
 * \date 2011/09/16 17:35
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONQUARTMOVETO_H_
#define __ACTIONQUARTMOVETO_H_

#include "IActionBase.h"
#include "ActionMoveTo.h"

class ActionQuartMoveTo : public ActionMoveTo
{
public:
	DECLARE_RTTI(ActionQuartMoveTo, ActionMoveTo);
public:
	ActionQuartMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionQuartMoveTo();

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();

protected:
	virtual float Interpolate();
private:
	ACTION_TWEEN_TYPE m_eType;
};
#endif//__ACTIONQUARTMOVETO_H_