package com.zjhlogo.spank.msg;

import android.app.Activity;

public class MsgDestroyButton extends MsgBase
{
	private Activity mActivity = null;
	private int mButtonId = 0;
	
	public MsgDestroyButton(Activity activity, int btnId)
	{
		super(MSG_ID.MI_DESTROY_BUTTON);
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
