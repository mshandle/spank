/*!
 * \file MsgNotifyPublicCards.h
 * \date unknown
 * 
 * ������ʾ
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGNOTIFYPUBLICCARDS_H__
#define __MSGNOTIFYPUBLICCARDS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgNotifyPublicCards : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2015,
		MSG_SIZE = 16,
	};

public:
	DECLARE_RTTI(MsgNotifyPublicCards, PokerMsgBase);

	MsgNotifyPublicCards();
	virtual ~MsgNotifyPublicCards();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	char nCount;	// ����, ��һ�η���Ϊ3��, �ڶ���4��, ������5��
	char nCards[5];	// ��ΧΪ0~51, ��ʾ52�����е�һ��
	char _dummy[2];	// ����λ

};

#endif // __MSGNOTIFYPUBLICCARDS_H__