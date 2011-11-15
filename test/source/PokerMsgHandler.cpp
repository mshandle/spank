/*!
 * \file PokerMsgHandler.cpp
 * \date 11-15-2011 14:54:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PokerMsgHandler.h"
#include <util/IDebugUtil.h>

PokerMsgHandler::PokerMsgHandler()
{
	// TODO: 
}

PokerMsgHandler::~PokerMsgHandler()
{
	// TODO: 
}

bool PokerMsgHandler::DecodeData(const void* pData, int nLength)
{
	const char* pBytes = (const char*)pData;
	for (int i = 0; i < nLength; ++i)
	{
		m_vMessageData.push_back(pBytes[i]);
	}
	if (m_vMessageData.size() <= 0) return false;

	// decode the message
	StreamReader reader(&m_vMessageData[0], m_vMessageData.size());
	short nSize = 0;
	if (!reader.Read(&nSize, sizeof(nSize))) return false;
	if (nSize < (int)m_vMessageData.size()) return false;

	short nType = 0;
	if (!reader.Read(&nType, sizeof(nType))) return false;

	// dispatch the message (nMsgId, &m_vMessageData[0], nSize)
	CallHandler(nType, &m_vMessageData[0], nSize);
	LOGD("receive message: type %d, size:%d", nType, nSize);

	m_vMessageData.erase(m_vMessageData.begin(), m_vMessageData.begin()+nSize);
	return true;
}

void PokerMsgHandler::Reset()
{
	m_vMessageData.clear();
	m_HandlerInfoMap.clear();
}

bool PokerMsgHandler::RegisterMessage(short nType, IMsgHandler* pHandler, NET_MSG_CALLBACK pCallback)
{
	if (!pHandler || !pCallback) return false;

	if (FindHandlerInfo(nType, pHandler) != m_HandlerInfoMap.end())
	{
		LOGE("duplicate register message %d", nType);
		return false;
	}

	HANDLER_INFO info = {nType, pHandler, pCallback};
	m_HandlerInfoMap.insert(std::make_pair(nType, info));
	return true;
}

bool PokerMsgHandler::UnregisterMessage(short nType)
{
	std::pair<TM_HANDLER_INFO::iterator, TM_HANDLER_INFO::iterator> range = m_HandlerInfoMap.equal_range(nType);
	if (range.first == m_HandlerInfoMap.end()) return false;

	m_HandlerInfoMap.erase(range.first, range.second);
	return true;
}

PokerMsgHandler::TM_HANDLER_INFO::iterator PokerMsgHandler::FindHandlerInfo(short nType, IMsgHandler* pHandler)
{
	std::pair<TM_HANDLER_INFO::iterator, TM_HANDLER_INFO::iterator> range = m_HandlerInfoMap.equal_range(nType);
	for (TM_HANDLER_INFO::iterator it = range.first; it != range.second; ++it)
	{
		HANDLER_INFO& handlerInfo = it->second;
		if (handlerInfo.pHandler == pHandler) return it;
	}

	return m_HandlerInfoMap.end();
}

bool PokerMsgHandler::CallHandler(short nType, const void* pData, int nLength)
{
	// collect all connection info in stack, in case of caller delete itself
	TV_HANDLER_INFO vHandlerInfo;
	std::pair<TM_HANDLER_INFO::iterator, TM_HANDLER_INFO::iterator> range = m_HandlerInfoMap.equal_range(nType);
	for (TM_HANDLER_INFO::iterator it = range.first; it != range.second; ++it)
	{
		HANDLER_INFO& handlerInfo = it->second;
		vHandlerInfo.push_back(handlerInfo);
	}

	StreamReader reader(pData, nLength);

	// call event from stack
	int nFailedCount = 0;
	bool bResult = false;
	for (TV_HANDLER_INFO::iterator it = vHandlerInfo.begin(); it != vHandlerInfo.end(); ++it)
	{
		HANDLER_INFO& handlerInfo = (*it);

		IMsgHandler* pHandler = handlerInfo.pHandler;
		NET_MSG_CALLBACK pCallback = handlerInfo.pCallback;

		reader.Reset();
		bResult = (pHandler->*pCallback)(nType, &reader);
		if (!bResult) ++nFailedCount;
	}

	return (bResult && nFailedCount == 0);
}
