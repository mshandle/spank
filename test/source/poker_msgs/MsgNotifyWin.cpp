/*!
 * \file MsgNotifyWin.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyWin.h"

MsgNotifyWin::MsgNotifyWin()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyWin::~MsgNotifyWin()
{
	// TODO: 
}

bool MsgNotifyWin::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nPoolId, sizeof(nPoolId))) return false;
	if (!pReader->Read(&nSeatIds, sizeof(nSeatIds))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nBonus, sizeof(nBonus))) return false;
	return true;
}

bool MsgNotifyWin::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nPoolId, sizeof(nPoolId))) return false;
	if (!pWriter->Write(&nSeatIds, sizeof(nSeatIds))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nBonus, sizeof(nBonus))) return false;
	return true;
}
