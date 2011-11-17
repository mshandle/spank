/*!
 * \file NetMgr_Win32_Impl.cpp
 * \date 11-14-2011 14:56:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NetMgr_Win32_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>

INetMgr& INetMgr::GetInstance()
{
	static NetMgr_Win32_Impl s_NetMgr_Win32_Impl;
	return s_NetMgr_Win32_Impl;
}

NetMgr_Win32_Impl::NetMgr_Win32_Impl()
{
	m_socketClient = NULL;
	m_pNetMsgHandler = NULL;
}

NetMgr_Win32_Impl::~NetMgr_Win32_Impl()
{
	// TODO: 
}

bool NetMgr_Win32_Impl::Initialize()
{
	WSADATA wsaData;
	if (WSAStartup(0x0202, &wsaData) != 0) return false;

	return true;
}

void NetMgr_Win32_Impl::Terminate()
{
	Disconnect();
	WSACleanup();
}

void NetMgr_Win32_Impl::Update(float dt)
{
	// nothing to do
}

bool NetMgr_Win32_Impl::ConnectToServer(const char* ip, ushort port)
{
	bool bOk = ConnectToServer(inet_addr(ip), port);
	if (bOk)
	{
		LOGD("connect to server %s:%d success", ip, port);
	}
	else
	{
		LOGD("connect to server %s:%d failed", ip, port);
	}

	return bOk;
}

bool NetMgr_Win32_Impl::ConnectToServer(uint ip, ushort port)
{
	HWND hWnd = (HWND)ConfigUtil::GetInstance().GetPointer("NATIVE_WINDOW");
	if (!hWnd) return false;

	Disconnect();

	// init address
	SOCKADDR_IN addrServer;
	memset(&addrServer, 0, sizeof(addrServer));
	addrServer.sin_addr.S_un.S_addr = ip;
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);

	// create socket
	m_socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (m_socketClient == NULL) return false;

	// connect to server
	if (connect(m_socketClient, (SOCKADDR*)&addrServer, sizeof(SOCKADDR)) == SOCKET_ERROR)
	{
		Disconnect();
		return false;
	}

	WSAAsyncSelect(m_socketClient, hWnd, WM_SOCKET, FD_CONNECT|FD_READ|FD_WRITE|FD_CLOSE);
	return true;
}

void NetMgr_Win32_Impl::Disconnect()
{
	if (m_socketClient)
	{
		closesocket(m_socketClient);
		m_socketClient = NULL;
		LOGD("disconnect from server");
	}
}

bool NetMgr_Win32_Impl::SendNetMessage(INetMsgBase* pMsg)
{
	StreamWriter writer;
	if (!pMsg->ToStream(&writer))
	{
		LOGE("SendNetMessage %s::ToStream failed", pMsg->GetRtti()->GetTypeName());
		return false;
	}

	int length = writer.GetBufferSize();
	const char* pszBuffer = (const char*)writer.GetBuffer();

	int result = send(m_socketClient, pszBuffer, length, 0);
	if (result == SOCKET_ERROR)
	{
		int error = WSAGetLastError();
		LOGE("SendNetMessage %s failed with error code %d", pMsg->GetRtti()->GetTypeName(), error);
		return false;
	}

	if (result != length)
	{
		LOGE("SendNetMessage %s size miss-match origin:%d, sent:%d", pMsg->GetRtti()->GetTypeName(), length, result);
		return false;
	}

	return true;
}

void NetMgr_Win32_Impl::SetNetMsgHandler(INetMsgHandler* pHandler)
{
	m_pNetMsgHandler = pHandler;
}

INetMsgHandler* NetMgr_Win32_Impl::GetNetMsgHandler()
{
	return m_pNetMsgHandler;
}

bool NetMgr_Win32_Impl::HandlerDataBlock(const void* pData, int nLength)
{
	if (m_pNetMsgHandler == NULL)
	{
		LOGE("can not decode the data, no message decoder set");
		return false;
	}

	return m_pNetMsgHandler->DecodeData(pData, nLength);
}
