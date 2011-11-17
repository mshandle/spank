/*!
 * \file NetMgr_Android_Impl.cpp
 * \date 11-17-2011 8:53:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "NetMgr_Android_Impl.h"
#include <util/StringUtil.h>
#include <util/IDebugUtil.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ioctl.h>
#include <netinet/in.h>
#include <arpa/inet.h>

INetMgr& INetMgr::GetInstance()
{
	static NetMgr_Android_Impl s_NetMgr_Android_Impl;
	return s_NetMgr_Android_Impl;
}

NetMgr_Android_Impl::NetMgr_Android_Impl()
{
	m_nSocket = 0;
	m_pNetMsgHandler = NULL;
}

NetMgr_Android_Impl::~NetMgr_Android_Impl()
{
	// TODO: 
}

bool NetMgr_Android_Impl::Initialize()
{
	m_SendBuffer.Reset();
	return true;
}

void NetMgr_Android_Impl::Terminate()
{
	Disconnect();
}

void NetMgr_Android_Impl::Update(float dt)
{
	if (m_nSocket <= 0) return;

	// read from socket
	ReceiveOnce();

	// write to socket
	SendOnce();
}

bool NetMgr_Android_Impl::ConnectToServer(const char* ip, ushort port)
{
	uint nIP = 0;
	inet_pton(AF_INET, ip, &nIP);
	bool bOk = ConnectToServer(nIP, port);

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

bool NetMgr_Android_Impl::ConnectToServer(uint ip, ushort port)
{
	// disconnect from server
	Disconnect();

	// create socket
	m_nSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (m_nSocket < 0)
	{
		LOGD("create socket failed, socket: %d", m_nSocket);
		m_nSocket = 0;
		return false;
	}

 	// set non blocking socket
	int nOn = 1;
	ioctl(m_nSocket, FIONBIO, &nOn);

	// setup server address
	sockaddr_in addrServer;
	StringUtil::ZeroMemory(&addrServer, sizeof(addrServer));
	addrServer.sin_family = AF_INET;
	addrServer.sin_port = htons(port);
	addrServer.sin_addr.s_addr = ip;

	// connect to server
	int result = connect(m_nSocket, (struct sockaddr*)&addrServer, sizeof(addrServer));
	if (result < 0)
	{
		if (errno == EINPROGRESS) return true;
	}

	LOGD("connect failed, result: %d, errno: %d", result, errno);
	Disconnect();
	return false;
}

void NetMgr_Android_Impl::Disconnect()
{
	m_SendBuffer.Reset();

	if (m_nSocket != 0)
	{
		close(m_nSocket);
		m_nSocket = 0;
		LOGD("disconnect from server");
	}
}

bool NetMgr_Android_Impl::SendNetMessage(INetMsgBase* pMsg)
{
	StreamWriter writer;
	if (!pMsg->ToStream(&writer))
	{
		LOGE("SendNetMessage %s::ToStream failed", pMsg->GetRtti()->GetTypeName());
		return false;
	}

	int length = writer.GetBufferSize();
	const void* pszBuffer = writer.GetBuffer();
	m_SendBuffer.Write(pszBuffer, length);

	SendOnce();
	return true;
}

void NetMgr_Android_Impl::SetNetMsgHandler(INetMsgHandler* pHandler)
{
	m_pNetMsgHandler = pHandler;
}

INetMsgHandler* NetMgr_Android_Impl::GetNetMsgHandler()
{
	return m_pNetMsgHandler;
}

bool NetMgr_Android_Impl::HandlerDataBlock(const void* pData, int nLength)
{
	if (m_pNetMsgHandler == NULL)
	{
		LOGE("can not decode the data, no message decoder set");
		return false;
	}

	return m_pNetMsgHandler->DecodeData(pData, nLength);
}

void NetMgr_Android_Impl::ReceiveOnce()
{
	char buffer[1024];
	int result = read(m_nSocket, buffer, 1024);
	while (true)
	{
		if (result < 0)
		{
			if (errno != EWOULDBLOCK)
			{
				// TODO: read failed
			}

			break;
		}
		else if (result < 1024)
		{
			HandlerDataBlock(buffer, result);
			break;
		}

		result = read(m_nSocket, buffer, 1024);
	}
}

void NetMgr_Android_Impl::SendOnce()
{
	StreamReader reader(m_SendBuffer.GetBuffer(), m_SendBuffer.GetBufferSize());
	if (reader.GetSize() <= 0) return;

	int result = send(m_nSocket, (const char*)reader.GetBuffer(), reader.GetSize(), 0);
	while (true)
	{
		if (result <= 0)
		{
			if (errno != EWOULDBLOCK)
			{
				// TODO: send failed
			}
			break;
		}

		reader.Skip(result);
		if (reader.GetSize() <= 0) break;

		result = send(m_nSocket, (const char*)reader.GetBuffer(), reader.GetSize(), 0);
	}

	m_SendBuffer.Reset();
	// warring: copy the same memory block can be lose data
	m_SendBuffer.Write(reader.GetBuffer(), reader.GetSize());
}
