/*!
 * \file ActionBackMove.h
 * \date 2011/09/16 14:55
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __ACTIONBACKMOVE_H_
#define __ACTIONBACKMOVE_H_
#include "IActionBase.h"

class ActionBackMoveTo :public IActionBase
{
public:
	DECLARE_RTTI(ActionBackMoveTo, IActionBase);
public:
	ActionBackMoveTo(ACTION_TWEEN_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time);
	virtual ~ActionBackMoveTo();
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
#endif//__ACTIONBACKMOVE_H_