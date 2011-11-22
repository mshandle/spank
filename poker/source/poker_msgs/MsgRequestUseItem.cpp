/*!
 * \file MsgRequestUseItem.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestUseItem.h"

MsgRequestUseItem::MsgRequestUseItem()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestUseItem::~MsgRequestUseItem()
{
	// TODO: 
}

bool MsgRequestUseItem::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nItemId, sizeof(nItemId))) return false;
	return true;
}

bool MsgRequestUseItem::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nItemId, sizeof(nItemId))) return false;
	return true;
}
