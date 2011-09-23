/*!
 * \file IMsgHandler.cpp
 * \date 8-16-2011 11:25:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/IMsgHandler.h>
#include <util/IDebugUtil.h>

IMsgHandler::IMsgHandler()
{
	// TODO: 
}

IMsgHandler::~IMsgHandler()
{
	// TODO: 
}

bool IMsgHandler::ConnectEvent(uint nMsgID, IMsgHandler* pHandler, MSG_CALLBACK pCallback)
{
	if (nMsgID == 0 || !pHandler || !pCallback) return false;

	if (FindConnectInfo(nMsgID, pHandler) != m_ConnectionMap.end())
	{
		LOGD("duplicate connect event %d", nMsgID);
		return false;
	}

	CONNECTION_INFO info = {nMsgID, pHandler, pCallback};
	m_ConnectionMap.insert(std::make_pair(nMsgID, info));
	return true;
}

bool IMsgHandler::DisconnectEvent(uint nMsgID)
{
	std::pair<TM_CONNECTION_INFO::iterator, TM_CONNECTION_INFO::iterator> range = m_ConnectionMap.equal_range(nMsgID);
	if (range.first == m_ConnectionMap.end()) return false;

	m_ConnectionMap.erase(range.first, range.second);
	return true;
}

bool IMsgHandler::CallEvent(IMsgBase& msgBase)
{
	int nFailedCount = 0;
	bool bResult = false;

	std::pair<TM_CONNECTION_INFO::iterator, TM_CONNECTION_INFO::iterator> range = m_ConnectionMap.equal_range(msgBase.GetMsgID());
	for (TM_CONNECTION_INFO::iterator it = range.first; it != range.second; ++it)
	{
		CONNECTION_INFO& connectInfo = it->second;

		IMsgHandler* pHandler = connectInfo.pHandler;
		MSG_CALLBACK pCallback = connectInfo.pCallback;

		bResult = (pHandler->*pCallback)(&msgBase);
		if (!bResult) ++nFailedCount;
	}

	return (bResult && nFailedCount == 0);
}

IMsgHandler::TM_CONNECTION_INFO::iterator IMsgHandler::FindConnectInfo(uint nMsgID, IMsgHandler* pHandler)
{
	std::pair<TM_CONNECTION_INFO::iterator, TM_CONNECTION_INFO::iterator> range = m_ConnectionMap.equal_range(nMsgID);
	for (TM_CONNECTION_INFO::iterator it = range.first; it != range.second; ++it)
	{
		CONNECTION_INFO& connectInfo = it->second;
		if (connectInfo.pHandler == pHandler) return it;
	}

	return m_ConnectionMap.end();
}
