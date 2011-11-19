/*!
 * \file MsgRequestBuyItem.cpp
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#include "MsgRequestBuyItem.h"

MsgRequestBuyItem::MsgRequestBuyItem()
:PokerMsgBase(MSG_TYPE, MSG_SIZE)
{
	// TODO: 
}

MsgRequestBuyItem::~MsgRequestBuyItem()
{
	// TODO: 
}

bool MsgRequestBuyItem::Unpack(StreamReader* pReader)
{
	if (!pReader->Read(&nUserId, sizeof(nUserId))) return false;
	if (!pReader->Read(&nItemType, sizeof(nItemType))) return false;
	if (!pReader->Read(&nBuyMethod, sizeof(nBuyMethod))) return false;
	if (!pReader->Read(&nDestSeatId, sizeof(nDestSeatId))) return false;
	if (!pReader->Read(&_dummy, sizeof(_dummy))) return false;
	if (!pReader->Read(&nCashCouponId, sizeof(nCashCouponId))) return false;
	return true;
}

bool MsgRequestBuyItem::Pack(StreamWriter* pWriter)
{
	if (!pWriter->Write(&nUserId, sizeof(nUserId))) return false;
	if (!pWriter->Write(&nItemType, sizeof(nItemType))) return false;
	if (!pWriter->Write(&nBuyMethod, sizeof(nBuyMethod))) return false;
	if (!pWriter->Write(&nDestSeatId, sizeof(nDestSeatId))) return false;
	if (!pWriter->Write(&_dummy, sizeof(_dummy))) return false;
	if (!pWriter->Write(&nCashCouponId, sizeof(nCashCouponId))) return false;
	return true;
}
