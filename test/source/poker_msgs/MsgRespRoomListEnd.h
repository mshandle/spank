/*!
 * \file MsgRespRoomListEnd.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPROOMLISTEND_H__
#define __MSGRESPROOMLISTEND_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespRoomListEnd : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2004,
		MSG_SIZE = 0,
	};

public:
	DECLARE_RTTI(MsgRespRoomListEnd, PokerMsgBase);

	MsgRespRoomListEnd();
	virtual ~MsgRespRoomListEnd();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:

};

#endif // __MSGRESPROOMLISTEND_H__
