/*!
 * \file PokerGameApp.h
 * \date 11-22-2011 9:54:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __POKERGAMEAPP_H__
#define __POKERGAMEAPP_H__

#include <IGameApp.h>
#include "PokerSurfaceView.h"

class PokerGameApp : public IGameApp
{
public:
	DECLARE_RTTI(PokerGameApp, IGameApp);

	PokerGameApp();
	virtual ~PokerGameApp();

	virtual bool Initialize();
	virtual void Terminate();

private:
	PokerSurfaceView* m_pSurfaceView;

};
#endif // __POKERGAMEAPP_H__
