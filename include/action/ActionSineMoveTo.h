/*!
 * \file ActionSineMoveTo.h
 * \date 9-16-2011 22:32:31
 * 
 * 
 * \author wbaoqing (wbaoqing@gmail.com)
 */
#ifndef __ACTIONSINEMOVE_H_
#define __ACTIONSINEMOVE_H_
#include "IActionBase.h"
class ActionSineMoveTo :public IActionBase
{

public:
	DECLARE_RTTI(ActionSineMoveTo, IActionBase);
public:
	ActionSineMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionSineMoveTo();
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
#endif//__ACTIONSINEMOVE_H_