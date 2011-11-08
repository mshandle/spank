package com.zjhlogo.spank;

import java.util.Map;
import java.util.TreeMap;

import android.app.Activity;

import com.zjhlogo.spank.msg.MSG_ID;
import com.zjhlogo.spank.msg.MsgBase;
import com.zjhlogo.spank.msg.MsgCommand;

public class SpankLibrary
{
	private static Activity mActivity = null;
	private static Map<Integer, BaseScreen> mViewMap = new TreeMap<Integer, BaseScreen>();
	private static int mGenerateId = 1000;
	
	private static SpankAppRunnable mRunnable = null;
	private static Thread mThread = null;

	static
	{
		System.loadLibrary("android_test");
	}

	public static void startApp(Activity activity)
	{
		mActivity = activity;
		mRunnable = new SpankAppRunnable(activity);
		mThread = new Thread(mRunnable);
		mThread.start();
	}
	
	public static void stopApp()
	{
		mRunnable.request(new MsgCommand(MSG_ID.MI_REQUEST_STOP_APP));
		try
		{
			mThread.join();
		}
		catch (InterruptedException e)
		{
			e.printStackTrace();
		}
		mRunnable = null;
		mThread = null;
	}
	
	public static void request(MsgBase msg)
	{
		if (mRunnable != null) mRunnable.request(msg);
	}
	
	public static native boolean initialize(String zipFilePath, int surfaceWidth, int surfaceHeight);
	public static native void terminate();
	
	public static native void update();
	
	public static native void initializeRenderer();
	public static native void render();
	public static native void terminateRenderer();
	
	public static native void touchBegin(int index, float x, float y);
	public static native void touchMove(int index, float x, float y);
	public static native void touchEnd(int index, float x, float y);

	public static native void onKeyReturn();
	public static native void onKeyHome();
	
	public static int createNormalView()
	{
		int id = genNextViewId();
		BaseScreen screen = new BaseScreen(mActivity, R.layout.layout_normal);
		mViewMap.put(id, screen);
		return id;
	}
	
	public static int createOpenGLView()
	{
		int id = genNextViewId();
		BaseScreen screen = new GLES20Screen(mActivity, R.layout.layout_opengles_20);
		mViewMap.put(id, screen);
		return id;
	}
	
	public static boolean activeView(int id)
	{
		BaseScreen screen = mViewMap.get(id);
		if (screen == null) return false;

		screen.active();
		return true;
	}
	
	public static boolean deactiveView(int id)
	{
		BaseScreen screen = mViewMap.get(id);
		if (screen == null) return false;
		
		screen.deactive();
		return true;
	}
	
	public static void destroyView(int id)
	{
		BaseScreen screen = mViewMap.get(id);
		if (screen == null) return;
		
		mViewMap.remove(id);
		screen = null;
	}
	
	private static int genNextViewId()
	{
		return mGenerateId++;
	}
}
