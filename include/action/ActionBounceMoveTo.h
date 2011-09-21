/*!
 * \file ActionBounceMoveTo.h
 * \date 2011/09/19 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONBOUNCEMOVETO_H_
#define __ACTIONBOUNCEMOVETO_H_

#include "IActionBase.h"

class ActionBounceMoveTo : public IActionBase
{
public:
	DECLARE_RTTI(ActionBounceMoveTo, IActionBase);
public:
	ActionBounceMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time );
	virtual ~ActionBounceMoveTo();
	virtual void Reset() ;
	virtual void Update(float dt) ;

	virtual IActionBase* Clone() ;
	virtual IActionBase* CloneInverse();

	virtual float GetTimeLength() const;
private:
	Vector3 Tween();
	Vector3 BounceTween(float t, const Vector3& b, const Vector3& c, float d);
private:
	Vector3 m_vPosStart;
	Vector3 m_vPosEnd;
	float m_fTime;

	float m_fCurrTime;
	float m_fAttenuation;
	ACTION_TWEEN_TYPE m_eType;

};
#endif//__ACTIONBOUNCEMOVETO_H_