package com.zjhlogo.spank;

import java.util.Map;
import java.util.TreeMap;

import android.app.Activity;
import android.view.SurfaceHolder;

import com.zjhlogo.spank.msg.MSG_ID;
import com.zjhlogo.spank.msg.MsgBase;
import com.zjhlogo.spank.msg.MsgCommand;

public class SpankLibrary
{
	private static Activity mActivity = null;
	private static Map<Integer, BaseView> mViewMap = new TreeMap<Integer, BaseView>();
	private static int mGenerateId = 1000;
	
	private static SpankAppRunnable mRunnable = null;
	private static Thread mThread = null;

	private static SpankRenderer mRenderer = null;

	static
	{
		System.loadLibrary("android_test");
	}

	// ui thread call it
	public static void startApp(Activity activity)
	{
		clear();
		
		mActivity = activity;
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
		mViewMap.clear();
		mGenerateId = 1000;
		mRunnable = null;
		mThread = null;
	}

	// game thread call it
	public static int createNormalView()
	{
		int id = genNextViewId();
		BaseView view = new NormalView();
		mViewMap.put(id, view);
		return id;
	}
	
	// game thread call it
	public static int createOpenGLView()
	{
		int id = genNextViewId();
		BaseView view = new GLES20View();
		mViewMap.put(id, view);
		return id;
	}
	
	// game thread call it
	public static boolean activeView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return false;

		return view.active(mActivity);
	}
	
	// game thread call it
	public static boolean deactiveView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return false;
		
		view.deactive(mActivity);
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
	
	public static boolean initializeRenderer(SurfaceHolder holder)
	{
		mRenderer = new SpankRenderer(holder);
		if (!mRenderer.initializeRenderer())
		{
			mRenderer = null;
			return false;
		}
		
		return true;
	}
	
	public static void terminateRenderer()
	{
		if (mRenderer != null)
		{
			mRenderer.terminateRenderer();
			mRenderer = null;
		}
	}

	public static void renderIfNessary()
	{
		if (mRenderer != null)
		{
			mRenderer.BeginRender();
			render();
			mRenderer.EndRender();
		}
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
