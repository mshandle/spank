/*!
 * \file ActionExpoMoveTo.h
 * \date 9-16-2011 22:32:31
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#ifndef __ACTIONEXPOMOVE_H_
#define __ACTIONEXPOMOVE_H_

#include "IActionBase.h"
#include "ActionMoveTo.h"

class ActionExpoMoveTo :public ActionMoveTo
{
public:
	DECLARE_RTTI(ActionExpoMoveTo, ActionMoveTo);
public:
	ActionExpoMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionExpoMoveTo();

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();
protected:
	virtual float Interpolate();

private:
	ACTION_TWEEN_TYPE m_eType;
};
#endif//__ACTIONEXPOMOVE_H_