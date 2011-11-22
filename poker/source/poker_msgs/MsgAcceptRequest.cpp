/*!
 * \file MsgAcceptRequest.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgAcceptRequest.h"

MsgAcceptRequest::MsgAcceptRequest()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgAcceptRequest::~MsgAcceptRequest()
{
	// TODO: 
}

bool MsgAcceptRequest::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nAcceptUserId, sizeof(nAcceptUserId))) return false;
	if (!pReader->Read(&nRequestUserId, sizeof(nRequestUserId))) return false;
	if (!pReader->Read(&nRequestId, sizeof(nRequestId))) return false;
	if (!pReader->Read(&nRequestType, sizeof(nRequestType))) return false;
	return true;
}

bool MsgAcceptRequest::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nAcceptUserId, sizeof(nAcceptUserId))) return false;
	if (!pWriter->Write(&nRequestUserId, sizeof(nRequestUserId))) return false;
	if (!pWriter->Write(&nRequestId, sizeof(nRequestId))) return false;
	if (!pWriter->Write(&nRequestType, sizeof(nRequestType))) return false;
	return true;
}
