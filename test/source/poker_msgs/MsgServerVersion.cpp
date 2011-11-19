/*!
 * \file MsgServerVersion.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgServerVersion.h"

MsgServerVersion::MsgServerVersion()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgServerVersion::~MsgServerVersion()
{
	// TODO: 
}

bool MsgServerVersion::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nVersionId, sizeof(nVersionId))) return false;
	if (!pReader->Read(&nYear, sizeof(nYear))) return false;
	if (!pReader->Read(&nMonth, sizeof(nMonth))) return false;
	if (!pReader->Read(&nDay, sizeof(nDay))) return false;
	if (!pReader->Read(&nHour, sizeof(nHour))) return false;
	if (!pReader->Read(&nMinute, sizeof(nMinute))) return false;
	if (!pReader->Read(&nSecond, sizeof(nSecond))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	return true;
}

bool MsgServerVersion::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nVersionId, sizeof(nVersionId))) return false;
	if (!pWriter->Write(&nYear, sizeof(nYear))) return false;
	if (!pWriter->Write(&nMonth, sizeof(nMonth))) return false;
	if (!pWriter->Write(&nDay, sizeof(nDay))) return false;
	if (!pWriter->Write(&nHour, sizeof(nHour))) return false;
	if (!pWriter->Write(&nMinute, sizeof(nMinute))) return false;
	if (!pWriter->Write(&nSecond, sizeof(nSecond))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	return true;
}
