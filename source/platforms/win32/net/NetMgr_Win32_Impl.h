/*!
 * \file NetMgr_Win32_Impl.h
 * \date 11-14-2011 14:51:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NETMGR_WIN32_IMPL_H__
#define __NETMGR_WIN32_IMPL_H__

#include <net/INetMgr.h>
#include <WinSock2.h>

class NetMgr_Win32_Impl : public INetMgr
{
public:
	enum CONST_DEFINE
	{
		WM_SOCKET = 0x0400 + 1,			// WM_USER + 1
	};

public:
	DECLARE_RTTI(NetMgr_Win32_Impl, INetMgr);

	NetMgr_Win32_Impl();
	virtual ~NetMgr_Win32_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual bool ConnectToServer(const char* ip, ushort port);
	virtual bool ConnectToServer(uint ip, ushort port);
	virtual void Disconnect();

	virtual bool SendNetMessage(INetMsgBase* pMsg);

	virtual void SetNetMsgHandler(INetMsgHandler* pHandler);
	virtual INetMsgHandler* GetNetMsgHandler();
	virtual bool HandlerDataBlock(const void* pData, int nLength);

private:
	SOCKET m_socketClient;
	INetMsgHandler* m_pNetMsgHandler;

};
#endif // __NETMGR_WIN32_IMPL_H__
