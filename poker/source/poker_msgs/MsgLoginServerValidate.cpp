/*!
 * \file MsgLoginServerValidate.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgLoginServerValidate.h"

MsgLoginServerValidate::MsgLoginServerValidate()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgLoginServerValidate::~MsgLoginServerValidate()
{
	// TODO: 
}

bool MsgLoginServerValidate::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&szIp, sizeof(szIp))) return false;
	if (!pReader->Read(&nPort, sizeof(nPort))) return false;
	if (!pReader->Read(&szCheckOutText, sizeof(szCheckOutText))) return false;
	if (!pReader->Read(&nIggId, sizeof(nIggId))) return false;
	return true;
}

bool MsgLoginServerValidate::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&szIp, sizeof(szIp))) return false;
	if (!pWriter->Write(&nPort, sizeof(nPort))) return false;
	if (!pWriter->Write(&szCheckOutText, sizeof(szCheckOutText))) return false;
	if (!pWriter->Write(&nIggId, sizeof(nIggId))) return false;
	return true;
}
