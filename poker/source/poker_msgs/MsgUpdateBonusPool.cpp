/*!
 * \file MsgUpdateBonusPool.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgUpdateBonusPool.h"

MsgUpdateBonusPool::MsgUpdateBonusPool()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgUpdateBonusPool::~MsgUpdateBonusPool()
{
	// TODO: 
}

bool MsgUpdateBonusPool::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nPool, sizeof(nPool))) return false;
	return true;
}

bool MsgUpdateBonusPool::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nPool, sizeof(nPool))) return false;
	return true;
}
