package com.zjhlogo.spank;

import android.app.Activity;

import com.zjhlogo.spank.msg.MsgBase;

public abstract class MessageRunnable implements Runnable
{
	private MsgBase mMsg = null;
	private boolean mBlocking = false;
	
	public MessageRunnable(MsgBase msg)
	{
		mMsg = msg;
	}
	
	public void run()
	{
		runOnUiThread();
		unblock();
	}
	
	public abstract void runOnUiThread();
	
	public MsgBase getMsg()
	{
		return mMsg;
	}
	
	public void syncRunOnUiThread(Activity activity)
	{
		block();
		activity.runOnUiThread(this);
		while (isBlocking());
	}
	
	private void block()
	{
		mBlocking = true;
	}
	
	private void unblock()
	{
		mBlocking = false;
	}
	
	private boolean isBlocking()
	{
		return mBlocking;
	}
}
