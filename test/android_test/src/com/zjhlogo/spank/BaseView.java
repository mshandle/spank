package com.zjhlogo.spank;

import android.app.Activity;
import android.view.View;

public class BaseView
{
	private int mResId = R.layout.layout_empty;
	private boolean mLock = false;
	
	public BaseView(int resId)
	{
		mResId = resId;
	}
	
	public boolean active(Activity activity)
	{
		View view = activity.getLayoutInflater().inflate(mResId, null, false);
		activity.setContentView(view);
		return true;
	}

	public void deactive(Activity activity)
	{
		activity.setContentView(R.layout.layout_empty);
	}
	
	public void Lock()
	{
		mLock = true;
	}
	
	public void Unlock()
	{
		mLock = false;
	}
	
	public boolean isLocked()
	{
		return mLock;
	}
}
