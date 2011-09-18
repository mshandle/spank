/*!
 * \file ActionCubicMove.h
 * \date 2011/09/16 16:51
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONCUBICMOVE_H_
#define __ACTIONCUBICMOVE_H_

#include "IActionBase.h"

class ActionCubicMoveTo : public IActionBase
{
public:
	DECLARE_RTTI(ActionCubicMoveTo, IActionBase);
public:
	ActionCubicMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionCubicMoveTo();
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
#endif//__ACTIONCUBICMOVE_H_