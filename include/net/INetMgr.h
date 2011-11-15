/*!
 * \file INetMgr.h
 * \date 11-14-2011 14:52:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __INETMGR_H__
#define __INETMGR_H__

#include "../ISingleton.h"
#include "INetMsgBase.h"
#include "INetMsgHandler.h"

class INetMgr : public ISingleton
{
public:
	DECLARE_RTTI(INetMgr, ISingleton);

	static INetMgr& GetInstance();

	virtual bool ConnectToServer(const char* ip, ushort port) = 0;
	virtual bool ConnectToServer(uint ip, ushort port) = 0;
	virtual void Disconnect() = 0;

	virtual bool SendNetMessage(INetMsgBase* pMsg) = 0;

	virtual void SetNetMsgHandler(INetMsgHandler* pHandler) = 0;
	virtual INetMsgHandler* GetNetMsgHandler() = 0;
	virtual bool HandlerDataBlock(const void* pData, int nLength) = 0;

};
#endif // __INETMGR_H__
