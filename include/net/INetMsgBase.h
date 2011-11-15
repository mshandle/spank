/*!
 * \file INetMsgBase.h
 * \date 11-14-2011 15:01:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __INETMSGBASE_H__
#define __INETMSGBASE_H__

#include "../msg/IMsgBase.h"
#include "../StreamReader.h"
#include "../StreamWriter.h"

class INetMsgBase : public IMsgBase
{
public:
	DECLARE_RTTI(INetMsgBase, IMsgBase);

	INetMsgBase();
	virtual ~INetMsgBase();

	virtual bool FromStream(StreamReader* pReader) = 0;
	virtual bool ToStream(StreamWriter* pWriter) = 0;

};
#endif // __INETMSGBASE_H__
