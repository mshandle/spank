/*!
 * \file NetMgr_Android_Impl.h
 * \date 11-17-2011 8:52:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NETMGR_ANDROID_IMPL_H__
#define __NETMGR_ANDROID_IMPL_H__

#include <net/INetMgr.h>

class NetMgr_Android_Impl : public INetMgr
{
public:
	DECLARE_RTTI(NetMgr_Android_Impl, INetMgr);

	NetMgr_Android_Impl();
	virtual ~NetMgr_Android_Impl();

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
#endif // __NETMGR_ANDROID_IMPL_H__
