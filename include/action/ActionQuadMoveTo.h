/*!
 * \file ActionQuadraticMove.h
 * \date 2011/09/16 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONTWEENMOVE_H_
#define __ACTIONTWEENMOVE_H_

#include "IActionBase.h"
#include "ActionMoveTo.h"

class ActionQuadMoveTo : public ActionMoveTo
{
public:
	DECLARE_RTTI(ActionQuadMoveTo, ActionMoveTo);
public:
	ActionQuadMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionQuadMoveTo();

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();
	
protected:
	virtual float Interpolate();
private:
	
	ACTION_TWEEN_TYPE m_eType;
};
#endif//__ACTIONTWEENMOVE_H_