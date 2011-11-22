/*!
 * \file PokerSurfaceView.h
 * \date 11-22-2011 10:00:20
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __POKERSURFACEVIEW_H__
#define __POKERSURFACEVIEW_H__

#include <IViewOpenGL.h>

class PokerSurfaceView : public IViewOpenGL
{
public:
	DECLARE_RTTI(PokerSurfaceView, IViewOpenGL);

	PokerSurfaceView();
	virtual ~PokerSurfaceView();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	bool OnMsgTouch(IMsgBase* pMsg);

private:

};
#endif // __POKERSURFACEVIEW_H__
