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

class ActionQuartMoveTo : public IActionBase
{
public:
	DECLARE_RTTI(ActionQuartMoveTo, IActionBase);
public:
	ActionQuartMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionQuartMoveTo();
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
#endif//__ACTIONQUARTMOVETO_H_