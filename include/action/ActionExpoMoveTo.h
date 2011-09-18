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

class ActionExpoMoveTo :public IActionBase
{
public:
	DECLARE_RTTI(ActionExpoMoveTo, IActionBase);
public:
	ActionExpoMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionExpoMoveTo();
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
#endif//__ACTIONEXPOMOVE_H_