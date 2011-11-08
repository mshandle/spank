/*!
 * \file GameApp.h
 * \date 7-21-2011 14:42:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

#include <IGameApp.h>
#include <msg/IMsgBase.h>
#include <IViewNormal.h>

class GameApp : public IGameApp
{
public:
	DECLARE_RTTI(GameApp, IGameApp);

	GameApp();
	virtual ~GameApp();

	virtual bool Initialize();
	virtual void Terminate();

private:
	bool OnMsgKey(IMsgBase* pMsg);

private:
	IViewNormal* m_pView[2];
	int m_nIndex;

};
#endif // __GAMEAPP_H__
