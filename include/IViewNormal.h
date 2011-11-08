/*!
 * \file IViewNormal.h
 * \date 11-08-2011 10:14:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IVIEWNORMAL_H__
#define __IVIEWNORMAL_H__

#include "IObject.h"
#include "ISurfaceView.h"

class IViewNormal : public IObject
{
public:
	DECLARE_RTTI(IViewNormal, IObject);

	IViewNormal();
	IViewNormal(ISurfaceView* pSurfaceView);
	virtual ~IViewNormal();

	virtual bool OnAttachWindow();
	virtual bool OnDettachWindow();

	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;

	virtual void Update(float dt) = 0;

protected:
	void SetSurfaceView(ISurfaceView* pSurfaceView);

private:
	bool Create();

private:
	ISurfaceView* m_pSurfaceView;

};
#endif // __IVIEWNORMAL_H__
