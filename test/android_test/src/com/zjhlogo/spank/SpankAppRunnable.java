package com.zjhlogo.spank;

import java.util.LinkedList;
import java.util.Queue;

import android.app.Activity;
import android.util.DisplayMetrics;

import com.zjhlogo.spank.msg.MsgBase;

public class SpankAppRunnable implements Runnable
{
	private Activity mActivity = null;
	private boolean mRunning = false;
	
	private Queue<MsgBase> mMsgQueue = new LinkedList<MsgBase>();
	private byte[] lock = new byte[0];

	public SpankAppRunnable(Activity activity)
	{
		mActivity = activity;
	}
	
	public void request(MsgBase msg)
	{
		synchronized (lock)
		{
			mMsgQueue.offer(msg);
		}
	}
	
	private MsgBase pollMessage()
	{
		synchronized (lock)
		{
			MsgBase msg = mMsgQueue.poll();
			return msg;
		}
	}
	
	public void run()
	{
		if (initializeApp())
		{
			mRunning = true;
			
			while (mRunning)
			{
				MsgBase msg = pollMessage();
				while (msg != null)
				{
					processMessage(msg);
					msg = pollMessage();
				}
				
				// update
				SpankLibrary.update();
				
				// render if nessary
				SpankLibrary.renderIfNessary();
			}
		}
		
		terminateApp();
	}

	private boolean initializeApp()
	{
        DisplayMetrics dm = new DisplayMetrics();
        mActivity.getWindowManager().getDefaultDisplay().getMetrics(dm);
        
        // set the resource package path
		String packageName = mActivity.getPackageResourcePath();
		return SpankLibrary.initialize(packageName, dm.widthPixels, dm.heightPixels);
	}
	
	private void terminateApp()
	{
		SpankLibrary.terminate();
	}
	
	private void processMessage(MsgBase msg)
	{
		switch (msg.getId())
		{
		case MI_REQUEST_STOP_APP:
		{
			mRunning = false;
		}
		break;
		}
	}
}
