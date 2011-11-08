package com.zjhlogo.spank;

import java.util.Map;
import java.util.TreeMap;

import android.app.Activity;
import android.os.Handler;
import android.os.Message;

import com.zjhlogo.spank.msg.MSG_ID;
import com.zjhlogo.spank.msg.MsgBase;
import com.zjhlogo.spank.msg.MsgCommand;

public class SpankLibrary
{
	private static Activity mActivity = null;
	private static Handler mHandler = null;
	private static Map<Integer, BaseView> mViewMap = new TreeMap<Integer, BaseView>();
	private static int mGenerateId = 1000;
	
	private static SpankAppRunnable mRunnable = null;
	private static Thread mThread = null;

	static
	{
		System.loadLibrary("android_test");
	}

	// ui thread call it
	public static void startApp(Activity activity, Handler handler)
	{
		clear();
		
		mActivity = activity;
		mHandler = handler;
		mRunnable = new SpankAppRunnable(activity);
		mThread = new Thread(mRunnable);
		mThread.start();
	}
	
	// ui thread call it
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
		
		clear();
	}
	
	// ui thread call it
	private static void clear()
	{
		mActivity = null;
		mHandler = null;
		mViewMap.clear();
		mGenerateId = 1000;
		mRunnable = null;
		mThread = null;
	}

	// game thread call it
	public static int createNormalView()
	{
		int id = genNextViewId();
		BaseView view = new BaseView(R.layout.layout_normal);
		mViewMap.put(id, view);
		return id;
	}
	
	// game thread call it
	public static int createOpenGLView()
	{
		int id = genNextViewId();
		BaseView view = new GLES20View(R.layout.layout_opengles_20);
		mViewMap.put(id, view);
		return id;
	}
	
	// game thread call it
	public static boolean activeView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return false;

		// request active view
		Message msg = new Message();
		msg.what = SpankActivity.REQUEST_ACTIVE_VIEW;
		msg.obj = view;
		mHandler.sendMessage(msg);
		
		view.Lock();
		while (view.isLocked());		// 等待UI线程执行结束

		return true;
	}
	
	// game thread call it
	public static boolean deactiveView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return false;
		
		// request deactive view
		Message msg = new Message();
		msg.what = SpankActivity.REQUEST_DEACTIVE_VIEW;
		msg.obj = view;
		mHandler.sendMessage(msg);
		
		view.Lock();
		while (view.isLocked());		// 等待UI线程执行结束
		
		return true;
	}
	
	// game thread call it
	public static void destroyView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return;
		
		mViewMap.remove(id);
		view = null;
	}
	
	// game thread call it
	private static int genNextViewId()
	{
		return mGenerateId++;
	}
	
	// all thread can call it
	public static void request(MsgBase msg)
	{
		if (mRunnable != null) mRunnable.request(msg);
	}
	
	// game call them
	public static native boolean initialize(String zipFilePath, int surfaceWidth, int surfaceHeight);
	public static native void terminate();
	public static native void update();
	public static native void render();

	// ui thread call them
	public static native void touchBegin(int index, float x, float y);
	public static native void touchMove(int index, float x, float y);
	public static native void touchEnd(int index, float x, float y);
	public static native void onKeyReturn();
	public static native void onKeyHome();
}
