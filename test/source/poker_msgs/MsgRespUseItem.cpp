/*!
 * \file MsgRespUseItem.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespUseItem.h"

MsgRespUseItem::MsgRespUseItem()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespUseItem::~MsgRespUseItem()
{
	// TODO: 
}

bool MsgRespUseItem::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nItemId, sizeof(nItemId))) return false;
	if (!pReader->Read(&nIsSuccess, sizeof(nIsSuccess))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgRespUseItem::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nItemId, sizeof(nItemId))) return false;
	if (!pWriter->Write(&nIsSuccess, sizeof(nIsSuccess))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
