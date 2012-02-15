/*!
 * \file MsgRequestRoomList.h
 * \date unknown
 * 
 * �ͻ������󷿼��б�
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGREQUESTROOMLIST_H__
#define __MSGREQUESTROOMLIST_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRequestRoomList : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2002,
		MSG_SIZE = 12,
	};

public:
	DECLARE_RTTI(MsgRequestRoomList, PokerMsgBase);

	MsgRequestRoomList();
	virtual ~MsgRequestRoomList();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	int64 nUserId;
	int nRoomType;	// 0: ��ͨ��, 6: ���ٷ�, 10: Sit  Go����, 11: ����Sit  Go����, 

};

#endif // __MSGREQUESTROOMLIST_H__