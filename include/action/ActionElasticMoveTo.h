/*!
 * \file ActionElasticMoveTo.h
 * \date 2011/09/19 9:32
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONELASTICMOVETO_H_
#define __ACTIONELASTICMOVETO_H_

#include "IActionBase.h"

class ActionElasticMoveTo : public IActionBase
{
public:
	DECLARE_RTTI(ActionElasticMoveTo, IActionBase);
public:
	ActionElasticMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time );
	virtual ~ActionElasticMoveTo();
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
	float m_fAttenuation;
	ACTION_TWEEN_TYPE m_eType;

};
#endif//__ACTIONELASTICMOVETO_H_