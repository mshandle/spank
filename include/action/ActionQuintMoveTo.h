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

class ActionQuintMoveTo :public IActionBase
{
public:
	DECLARE_RTTI(ActionQuintMoveTo, IActionBase);
public:
	ActionQuintMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionQuintMoveTo();
	virtual void Reset() ;
	virtual void Update(float dt) ;

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;
private:
	Vector3 Tween();
private:
	Vector3 m_vPosStart;
	Vector3 m_vPosEnd;
	float m_fTime;

	float m_fCurrTime;
	ACTION_TWEEN_TYPE m_eType;
};
#endif//__ACTIONQUINTMOVETO_H