package com.zjhlogo.spank;

import java.util.LinkedList;
import java.util.Queue;

import android.app.Activity;
import android.util.DisplayMetrics;

import com.zjhlogo.spank.msg.MsgBase;
import com.zjhlogo.spank.msg.MsgRequestSetupRenderer;

public class SpankAppRunnable implements Runnable {
	private Activity mActivity = null;
	private boolean mRunning = false;
	private boolean mRendering = false;
	private SpankRenderer mRenderer = null;
	
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
			mRendering = false;
			
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
				
				// render
				if (mRendering)
				{
					mRenderer.BeginRender();
					SpankLibrary.render();
					mRenderer.EndRender();
				}
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
		case MI_REQUEST_SETUP_RENDERER:
		{
			MsgRequestSetupRenderer rsr = (MsgRequestSetupRenderer) msg;
			if (mRenderer != null)
			{
				mRenderer.terminateRenderer();
				mRenderer = null;
				mRendering = false;
			}
			
			mRenderer = new SpankRenderer(rsr.getHolder());
			mRendering = mRenderer.initializeRenderer();
		}
		break;
		case MI_REQUEST_STOP_RENDERER:
		{
			if (mRenderer != null)
			{
				mRenderer.terminateRenderer();
				mRenderer = null;
				mRendering = false;
			}
		}
		break;
		}
	}
}
