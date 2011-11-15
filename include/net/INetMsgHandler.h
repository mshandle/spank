/*!
 * \file INetMsgHandler.h
 * \date 11-15-2011 14:32:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __INETMSGHANDLER_H__
#define __INETMSGHANDLER_H__

class INetMsgHandler
{
public:
	DECLARE_RTTI(INetMsgHandler, INoRtti);

	virtual bool DecodeData(const void* pData, int nLength) = 0;
	virtual void Reset() = 0;

};
#endif // __INETMSGHANDLER_H__
