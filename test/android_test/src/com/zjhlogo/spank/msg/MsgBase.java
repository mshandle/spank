package com.zjhlogo.spank.msg;

public class MsgBase
{
	private MSG_ID mId = MSG_ID.MI_UNKNOWN;
	
	public MsgBase(MSG_ID id)
	{
		mId = id;
	}
	
	public MSG_ID getId()
	{
		return mId;
	}
}
