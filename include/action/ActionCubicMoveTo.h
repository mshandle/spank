/*!
 * \file ActionCubicMove.h
 * \date 2011/09/16 16:51
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONCUBICMOVE_H_
#define __ACTIONCUBICMOVE_H_

#include "action/ActionMoveTo.h"

class ActionCubicMoveTo : public ActionMoveTo
{
public:
	DECLARE_RTTI(ActionCubicMoveTo, ActionMoveTo);
public:
	ActionCubicMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionCubicMoveTo();

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();

protected:
	virtual float Interpolate();
private:
	ACTION_TWEEN_TYPE m_eType;
};
#endif//__ACTIONCUBICMOVE_H_