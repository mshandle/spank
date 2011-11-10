/*!
 * \file NormalView.h
 * \date 11-08-2011 11:19:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NORMALVIEW_H__
#define __NORMALVIEW_H__

#include <IViewNormal.h>

class NormalView : public IViewNormal
{
public:
	DECLARE_RTTI(NormalView, IViewNormal);

	NormalView();
	virtual ~NormalView();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float dt);

private:
	void* m_pButton;

};
#endif // __NORMALVIEW_H__
