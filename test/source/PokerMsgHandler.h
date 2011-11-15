/*!
 * \file PokerMsgHandler.h
 * \date 11-15-2011 14:54:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __POKERMSGHANDLER_H__
#define __POKERMSGHANDLER_H__

#include <msg/IMsgHandler.h>
#include <net/INetMsgBase.h>
#include <net/INetMsgHandler.h>
#include <vector>

typedef bool (IMsgHandler::*NET_MSG_CALLBACK)(short nType, StreamReader* pReader);

class PokerMsgHandler : public INetMsgHandler
{
public:
	typedef std::vector<char> TV_MESSAGE_DATA;

	typedef struct HANDLER_INFO_tag
	{
		short nType;
		IMsgHandler* pHandler;
		NET_MSG_CALLBACK pCallback;
	} HANDLER_INFO;

	typedef std::multimap<uint, HANDLER_INFO> TM_HANDLER_INFO;
	typedef std::vector<HANDLER_INFO> TV_HANDLER_INFO;

public:
	DECLARE_RTTI(PokerMsgHandler, INetMsgHandler);

	PokerMsgHandler();
	virtual ~PokerMsgHandler();

	virtual bool DecodeData(const void* pData, int nLength);
	virtual void Reset();

	bool RegisterMessage(short nType, IMsgHandler* pHandler, NET_MSG_CALLBACK pCallback);
	bool UnregisterMessage(short nType);

private:
	TM_HANDLER_INFO::iterator FindHandlerInfo(short nType, IMsgHandler* pHandler);
	bool CallHandler(short nType, const void* pData, int nLength);

private:
	TV_MESSAGE_DATA m_vMessageData;
	TM_HANDLER_INFO m_HandlerInfoMap;

};
#endif // __POKERMSGHANDLER_H__
