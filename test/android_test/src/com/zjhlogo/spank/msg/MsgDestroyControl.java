package com.zjhlogo.spank.msg;

import android.app.Activity;

public class MsgDestroyControl extends MsgBase
{
	private Activity mActivity = null;
	private int mButtonId = 0;
	
	public MsgDestroyControl(Activity activity, int btnId)
	{
		super(MSG_ID.MI_DESTROY_CONTROL);
		mActivity = activity;
		mButtonId = btnId;
	}

	public Activity getActivity()
	{
		return mActivity;
	}
	
	public int getButtonId()
	{
		return mButtonId;
	}
}
