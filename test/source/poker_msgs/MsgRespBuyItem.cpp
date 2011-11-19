/*!
 * \file MsgRespBuyItem.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRespBuyItem.h"

MsgRespBuyItem::MsgRespBuyItem()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRespBuyItem::~MsgRespBuyItem()
{
	// TODO: 
}

bool MsgRespBuyItem::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nItemType, sizeof(nItemType))) return false;
	if (!pReader->Read(&nCashCouponId, sizeof(nCashCouponId))) return false;
	if (!pReader->Read(&nCashCouponBalance, sizeof(nCashCouponBalance))) return false;
	return true;
}

bool MsgRespBuyItem::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nItemType, sizeof(nItemType))) return false;
	if (!pWriter->Write(&nCashCouponId, sizeof(nCashCouponId))) return false;
	if (!pWriter->Write(&nCashCouponBalance, sizeof(nCashCouponBalance))) return false;
	return true;
}
