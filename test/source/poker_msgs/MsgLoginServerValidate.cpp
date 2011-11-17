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
	if (!pReader->Read(&userId, sizeof(userId))) return false;
	if (!pReader->Read(&ip, sizeof(ip))) return false;
	if (!pReader->Read(&port, sizeof(port))) return false;
	if (!pReader->Read(&checkoutText, sizeof(checkoutText))) return false;
	return true;
}

bool MsgLoginServerValidate::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&userId, sizeof(userId))) return false;
	if (!pWriter->Write(&ip, sizeof(ip))) return false;
	if (!pWriter->Write(&port, sizeof(port))) return false;
	if (!pWriter->Write(&checkoutText, sizeof(checkoutText))) return false;
	return true;
}
