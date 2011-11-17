/*!
 * \file NetMgr_Mac_Impl.h
 * \date 11-17-2011 12:28:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NETMGR_MAC_IMPL_H__
#define __NETMGR_MAC_IMPL_H__

#include <net/INetMgr.h>

class NetMgr_Mac_Impl : public INetMgr
{
public:
	DECLARE_RTTI(NetMgr_Mac_Impl, INetMgr);
	
	NetMgr_Mac_Impl();
	virtual ~NetMgr_Mac_Impl();
	
	virtual bool Initialize();
	virtual void Terminate();
	
	virtual void Update(float dt);
	
	virtual bool ConnectToServer(const char* ip, ushort port);
	virtual bool ConnectToServer(uint ip, ushort port);
	virtual void Disconnect();
	
	virtual bool SendNetMessage(INetMsgBase* pMsg);
	
	virtual void SetNetMsgHandler(INetMsgHandler* pHandler);
	virtual INetMsgHandler* GetNetMsgHandler();
	virtual bool HandlerDataBlock(const void* pData, int nLength);

private:
	void ReceiveOnce();
	void SendOnce();
	
private:
	int m_nSocket;
	StreamWriter m_SendBuffer;
	INetMsgHandler* m_pNetMsgHandler;
	
};

#endif // __NETMGR_MAC_IMPL_H__
