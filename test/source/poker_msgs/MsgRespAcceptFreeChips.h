/*!
 * \file MsgRespAcceptFreeChips.h
 * \date unknown
 * 
 * 
 * \author Auto Generate by MsgGen
 */
#ifndef __MSGRESPACCEPTFREECHIPS_H__
#define __MSGRESPACCEPTFREECHIPS_H__

#include "PokerMsgBase.h"
#include "NetDataType.h"

class MsgRespAcceptFreeChips : public PokerMsgBase
{
public:
	enum CONST_DEFINE
	{
		MSG_TYPE = 2049,
		MSG_SIZE = 26,
	};

public:
	DECLARE_RTTI(MsgRespAcceptFreeChips, PokerMsgBase);

	MsgRespAcceptFreeChips();
	virtual ~MsgRespAcceptFreeChips();

	virtual bool Unpack(StreamReader* pReader);
	virtual bool Pack(StreamWriter* pWriter);

public:
	char nResult;
	char _dummy;
	int64 nUserId;
	int64 nRequsetId;
	int64 nGeneratedChips;

};

#endif // __MSGRESPACCEPTFREECHIPS_H__
