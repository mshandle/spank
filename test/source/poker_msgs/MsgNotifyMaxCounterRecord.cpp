/*!
 * \file MsgNotifyMaxCounterRecord.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgNotifyMaxCounterRecord.h"

MsgNotifyMaxCounterRecord::MsgNotifyMaxCounterRecord()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgNotifyMaxCounterRecord::~MsgNotifyMaxCounterRecord()
{
	// TODO: 
}

bool MsgNotifyMaxCounterRecord::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nOldRecordUserId, sizeof(nOldRecordUserId))) return false;
	if (!pReader->Read(&nOldRecordCounter, sizeof(nOldRecordCounter))) return false;
	if (!pReader->Read(&nNewRecordUserId, sizeof(nNewRecordUserId))) return false;
	if (!pReader->Read(&nNewRecordCounter, sizeof(nNewRecordCounter))) return false;
	if (!pReader->Read(&nSmallBlind, sizeof(nSmallBlind))) return false;
	if (!pReader->Read(&nCount, sizeof(nCount))) return false;
	return true;
}

bool MsgNotifyMaxCounterRecord::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nOldRecordUserId, sizeof(nOldRecordUserId))) return false;
	if (!pWriter->Write(&nOldRecordCounter, sizeof(nOldRecordCounter))) return false;
	if (!pWriter->Write(&nNewRecordUserId, sizeof(nNewRecordUserId))) return false;
	if (!pWriter->Write(&nNewRecordCounter, sizeof(nNewRecordCounter))) return false;
	if (!pWriter->Write(&nSmallBlind, sizeof(nSmallBlind))) return false;
	if (!pWriter->Write(&nCount, sizeof(nCount))) return false;
	return true;
}
