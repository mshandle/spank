/*!
 * \file ActionBackMove.h
 * \date 2011/09/16 14:55
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONBACKMOVE_H_
#define __ACTIONBACKMOVE_H_

#include "action/ActionMoveTo.h"

class ActionBackMoveTo :public ActionMoveTo
{
public:
	DECLARE_RTTI(ActionBackMoveTo, ActionMoveTo);
public:
	ActionBackMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionBackMoveTo();

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();

protected:
	virtual float Interpolate();
private:
	ACTION_TWEEN_TYPE m_eType;
};
#endif//__ACTIONBACKMOVE_H_