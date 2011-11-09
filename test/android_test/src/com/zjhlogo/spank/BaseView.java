package com.zjhlogo.spank;

import android.app.Activity;

public abstract class BaseView
{
	private int mLayoutId = R.layout.layout_empty;
	private boolean mLock = false;
	
	public class ActiveRunnable implements Runnable
	{
		private BaseView mView = null;
		private Activity mActivity = null;
		
		public ActiveRunnable(BaseView view, Activity activity)
		{
			mView = view;
			mActivity = activity;
		}
		
		public void run()
		{
			mView.activeOnUiThread(mActivity);
		}
	}

	public class DeactiveRunnable implements Runnable
	{
		private BaseView mView = null;
		private Activity mActivity = null;
		
		public DeactiveRunnable(BaseView view, Activity activity)
		{
			mView = view;
			mActivity = activity;
		}
		
		public void run()
		{
			mView.deactiveOnUiThread(mActivity);
		}
	}

	public BaseView(int layoutId)
	{
		mLayoutId = layoutId;
	}
	
	public int getLayoutId()
	{
		return mLayoutId;
	}
	
	public boolean active(Activity activity)
	{
		// request active view
		blockThread();
		activity.runOnUiThread(new ActiveRunnable(this, activity));
		while (isBlocking());		// 等待UI线程执行结束

		return activeOnGameThread(activity);
	}

	public void deactive(Activity activity)
	{
		deactiveOnGameThread(activity);
		
		// request active view
		blockThread();
		activity.runOnUiThread(new DeactiveRunnable(this, activity));
		while (isBlocking());		// 等待UI线程执行结束
	}

	public void blockThread()
	{
		mLock = true;
	}
	
	public void unblockThread()
	{
		mLock = false;
	}
	
	public boolean isBlocking()
	{
		return mLock;
	}

	public abstract boolean activeOnUiThread(Activity activity);
	public abstract void deactiveOnUiThread(Activity activity);
	public abstract boolean activeOnGameThread(Activity activity);
	public abstract void deactiveOnGameThread(Activity activity);
}
