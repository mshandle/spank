package com.zjhlogo.spank.msg;

import android.app.Activity;

public class MsgCreateButton extends MsgBase
{
	private Activity mActivity = null;
	private int mX = 0;
	private int mY = 0;
	private String mText = null;
	private boolean success = false;
	private int mButtonId = 0;
	
	public MsgCreateButton(Activity activity, int x, int y, String text)
	{
		super(MSG_ID.MI_CREATE_BUTTON);
		
		mActivity = activity;
		mX = x;
		mY = y;
		mText = text;
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

	public String getText()
	{
		return mText;
	}

	public boolean isSuccess()
	{
		return success;
	}

	public void setSuccess(boolean success)
	{
		this.success = success;
	}
	
	public int getButtonId()
	{
		return mButtonId;
	}
	
	public void setButtonId(int id)
	{
		mButtonId = id;
	}
}
