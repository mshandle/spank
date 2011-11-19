/*!
 * \file MsgNotifyUpdateItem.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyUpdateItem.h"

MsgNotifyUpdateItem::MsgNotifyUpdateItem()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyUpdateItem::~MsgNotifyUpdateItem()
{
	// TODO: 
}

bool MsgNotifyUpdateItem::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nType, sizeof(nType))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&stItem, sizeof(stItem))) return false;
	return true;
}

bool MsgNotifyUpdateItem::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nType, sizeof(nType))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&stItem, sizeof(stItem))) return false;
	return true;
}
