/*!
 * \file IMsgHandler.h
 * \date 8-10-2011 10:44:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMSGHANDLER_H__
#define __IMSGHANDLER_H__

#include "../BaseType.h"
#include "../IRtti.h"
#include "IMsgBase.h"
#include <map>

class IMsgHandler;

/*! define the message handle function like this:
 *
 *      bool On[Object][Action](IMsgBase* pMsg);
 *
 *  ex: 
 *
 *      bool OnButtonClicked(ImsgBase* pMsg);
 *
 * if the return value is true means you have process this message,
 * otherwise you don't want to process this message, and the message
 * will pass to another appropriate object
 */
typedef bool (IMsgHandler::*MSG_CALLBACK)(IMsgBase* pMsg);

class IMsgHandler
{
public:
	typedef struct CONNECTION_INFO_tag
	{
		uint nMsgID;
		IMsgHandler* pHandler;
		MSG_CALLBACK pCallback;
	} CONNECTION_INFO;

	typedef std::map<uint, CONNECTION_INFO> TM_CONNECTION_INFO;

public:
	DECLARE_RTTI(IMsgHandler, INoRtti);

	IMsgHandler();
	virtual ~IMsgHandler();

	bool ConnectEvent(uint nMsgID, IMsgHandler* pHandler, MSG_CALLBACK pCallback);
	bool DisconnectEvent(uint nMsgID);

protected:
	bool CallEvent(IMsgBase& msgBase);

private:
	CONNECTION_INFO* FindConnectionInfo(uint nMsgID);

private:
	TM_CONNECTION_INFO m_ConnectionMap;

};

#endif // __IMSGHANDLER_H__
