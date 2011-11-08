/*!
 * \file IViewOpenGL.h
 * \date 11-08-2011 10:14:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IVIEWOPENGL_H__
#define __IVIEWOPENGL_H__

#include "IViewNormal.h"

class IViewOpenGL : public IViewNormal
{
public:
	DECLARE_RTTI(IViewOpenGL, IViewNormal);

	IViewOpenGL();
	virtual ~IViewOpenGL();

	virtual bool OnAttachWindow();
	virtual bool OnDettachWindow();

	virtual void BeginRender();
	virtual void Render() = 0;
	virtual void EndRender();

private:
	bool Create();

private:
	ISurfaceView* m_pSurfaceView;

};
#endif // __IVIEWOPENGL_H__
