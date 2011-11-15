/*!
 * \file MsgMgr.h
 * \date 8-10-2011 10:40:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGMGR_H__
#define __MSGMGR_H__

#include "../ISingleton.h"
#include "../IMutex.h"
#include "IMsgBase.h"
#include <map>
#include <queue>

/*! \brief a message managerment class
 *
 * MsgMgr used for handler and/or dispatch the message event form one object to
 * anthor object (Inheritanced from IMsgHandler). use SubscribeMessage() to
 * subscribe and handling the message. use UnsubscribeMessage() to un-subscribe
 * and un-handling the message. use SendMessage() to generate a message and send
 * it to objects who handling this message. (note: the message will not send 
 * immidielity, it's going to send just before the next IGameApp update (IGameApp::Update)).
 */
class MsgMgr : public ISingleton
{
public:
	/*! message subscribe information */
	typedef struct SUBSCRIBE_INFO_tag
	{
		uint nMsgID;					/*!< message identity \see MESSAGE_ID */
		IMsgHandler* pHandler;			/*!< message handler, the IMsgHandler who is going to handle the message */
		MSG_CALLBACK pCallback;			/*!< the callback function to receive the message */
	} SUBSCRIBE_INFO;

	/*! message subscribe information map */
	typedef std::multimap<uint, SUBSCRIBE_INFO> TM_SUBSCRIBE_INFO;

	/*! message object information */
	typedef struct MESSAGE_INFO_tag
	{
		uint nMsgID;					/*!< message identity \see MESSAGE_ID */
		IMsgBase* pMsg;					/*!< the message object */
	} MESSAGE_INFO;

	/*! message object information queue */
	typedef std::queue<MESSAGE_INFO> TQ_MESSAGE_INFO;

public:
	DECLARE_RTTI(MsgMgr, ISingleton);

	MsgMgr();
	virtual ~MsgMgr();

	/*!
	 * \brief get the instance of MsgMgr
	 * \return the instance of the MsgMgr
	 */
	static MsgMgr& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();

	/*!
	 * \brief send a message
	 *
	 * 
	 * \param pMsg the message object to send
	 */
	void SendMessage(IMsgBase* pMsg);
	
	/*!
	 * \brief dispatch the message to the handlers
	 *
	 * it is invoke by system before IGameApp update, it means all handlers
	 * who subscribe this message will receive the message event before IGameApp
	 * update. do not invoke this method manually, except you know what you are
	 * doing.
	 */
	void DispatchMessage();

	/*!
	 * \brief subscribe a message
	 *
	 * it means, to tell the MsgMgr that the object (pHandler) want to receive
	 * the message whitch the message identity is nMsgID by calling it's member
	 * function pCallback.
	 * \param nMsgID the message identity
	 * \param pHandler the handler object
	 * \param pCallback the callback function
	 * \return return true if subscribe success, otherwise return false
	 */
	bool SubscribeMessage(uint nMsgID, IMsgHandler* pHandler, MSG_CALLBACK pCallback);
	
	/*!
	 * \brief un-subscribe a message
	 * \param nMsgID the message identity
	 * \param pHandler the handler object
	 * \return return true if un-subscribe success, return false if can not find the 
	 *         subscribe information of which message identity is nMsgID and handler
	 *         is pHandler
	 */
	bool UnsubscribeMessage(uint nMsgID, IMsgHandler* pHandler);
	
	/*!
	 * \brief un-subscribe all messages of a handler
	 * \param pHandler the handler object
	 * \return return true if un-subscribe success, otherwise return false
	 */
	bool UnsubscribeMessage(IMsgHandler* pHandler);

private:
	
	/*!
	 * \brief find the subscribe information
	 * \param nMsgID the message identity \see MESSAGE_ID
	 * \param pHandler the handler object
	 * \return return the iterator of the TM_SUBSCRIBE_INFO, if not found return
	 *         TM_SUBSCRIBE_INFO::end()
	 */
	TM_SUBSCRIBE_INFO::iterator FindSubscribeInfo(uint nMsgID, IMsgHandler* pHandler);
	
	/*!
	 * \brief dispatch one message to handlers
	 * \param msgInfo the message information to dispatch
	 * \return return true if dispatch success, otherwise return false
	 */
	bool DispatchOneMessage(MESSAGE_INFO& msgInfo);

private:
	IMutex* m_pMutex;						/*!< the mutex object to keep it thread safe */
	TM_SUBSCRIBE_INFO m_SubscribeMsgMap;	/*!< the subscribe message map */
	TQ_MESSAGE_INFO m_MsgQueue;				/*!< the message object queue for dispatch */

};
#endif // __MSGMGR_H__
