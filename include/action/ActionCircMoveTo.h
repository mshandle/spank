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

class ActionCircMoveTo : public IActionBase
{
public:
	DECLARE_RTTI(ActionCircMoveTo, IActionBase);
public:
	ActionCircMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionCircMoveTo();
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
#endif//__ACTIONCIRCMOVETO_H_