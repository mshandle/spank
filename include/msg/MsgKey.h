/*!
 * \file MsgKey.h
 * \date 11-03-2011 15:28:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGKEY_H__
#define __MSGKEY_H__

#include "IMsgBase.h"

class MsgKey : public IMsgBase
{
public:
	enum KEY_TYPE
	{
		KT_UNKNOWN = 0,
		KT_HOME,
		KT_RETURN,
	};

public:
	DECLARE_RTTI(MsgKey, IMsgBase);

	MsgKey(KEY_TYPE eType);
	~MsgKey();

	KEY_TYPE GetKeyType();

	bool IsHome() const;
	bool IsReturn() const;

private:
	KEY_TYPE m_eKeyType;

};
#endif // __MSGKEY_H__
