package com.zjhlogo.spank.msg;

import android.app.Activity;

public class MsgCreateEditText extends MsgBase
{
	private Activity mActivity = null;
	private int mX = 0;
	private int mY = 0;
	private boolean success = false;
	private int mButtonId = 0;

	public MsgCreateEditText(Activity activity, int x, int y)
	{
		super(MSG_ID.MI_CREATE_EDIT_TEXT);
		
		mActivity = activity;
		mX = x;
		mY = y;
	}

	public Activity getActivity()
	{
		return mActivity;
	}
	
	public int getX()
	{
		return mX;
	}

	public int getY()
	{
		return mY;
	}

	public boolean isSuccess()
	{
		return success;
	}

	public void setSuccess(boolean success)
	{
		this.success = success;
	}
	
	public int getEditTextId()
	{
		return mButtonId;
	}
	
	public void setEditTextId(int id)
	{
		mButtonId = id;
	}
}
