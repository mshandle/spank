package com.zjhlogo.spank;

import java.util.Map;
import java.util.TreeMap;

import android.app.Activity;
import android.view.Gravity;
import android.view.SurfaceHolder;
import android.view.View;
import android.view.ViewGroup;
import android.widget.Button;
import android.widget.FrameLayout;

import com.zjhlogo.spank.msg.MSG_ID;
import com.zjhlogo.spank.msg.MsgBase;
import com.zjhlogo.spank.msg.MsgCommand;
import com.zjhlogo.spank.msg.MsgCreateButton;
import com.zjhlogo.spank.msg.MsgDestroyButton;

public class SpankLibrary
{
	public static final int GEN_VIEW_ID_BASE = 1000;
	public static final int GEN_CONTROL_ID_BASE = 10000;
	
	private static Activity mActivity = null;
	private static Map<Integer, BaseView> mViewMap = new TreeMap<Integer, BaseView>();
	
	private static int mGenViewId = GEN_VIEW_ID_BASE;
	private static int mGenControlId = GEN_CONTROL_ID_BASE;
	
	private static SpankAppRunnable mRunnable = null;
	private static Thread mThread = null;

	private static SpankRenderer mRenderer = null;
	
	static
	{
		System.loadLibrary("android_test");
	}

	// ui thread
	public static void startApp(Activity activity)
	{
		clear();
		
		mActivity = activity;
		mRunnable = new SpankAppRunnable(activity);
		mThread = new Thread(mRunnable);
		mThread.start();
	}
	
	// ui thread
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
	
	// ui thread
	private static void clear()
	{
		mActivity = null;
		mViewMap.clear();
		mGenViewId = GEN_VIEW_ID_BASE;
		mGenControlId = GEN_CONTROL_ID_BASE;
		mRunnable = null;
		mThread = null;
	}

	// game thread
	public static int createNormalView()
	{
		int id = genNextViewId();
		BaseView view = new NormalView();
		mViewMap.put(id, view);
		return id;
	}
	
	// game thread
	public static int createOpenGLView()
	{
		int id = genNextViewId();
		BaseView view = new GLES20View();
		mViewMap.put(id, view);
		return id;
	}
	
	// game thread
	public static int createButton(int viewId, int x, int y, int width, int height, String text)
	{
		BaseView view = mViewMap.get(viewId);
		if (view == null) return 0;
		
		MsgCreateButton msg = new MsgCreateButton(mActivity, x, y, text);
		msg.setButtonId(genNextControlId());
		MessageRunnable runnable = new MessageRunnable(msg)
		{
			public void runOnUiThread()
			{
				MsgCreateButton msg = (MsgCreateButton)getMsg();
				Activity activity = msg.getActivity();
				
		 		FrameLayout parent = (FrameLayout)activity.findViewById(R.id.frameLayout1);
				if (parent == null) return;
				
				Button button = new Button(activity);
				button.setId(msg.getButtonId());
				button.setText(msg.getText());
				
				FrameLayout.LayoutParams param = new FrameLayout.LayoutParams(ViewGroup.LayoutParams.WRAP_CONTENT, ViewGroup.LayoutParams.WRAP_CONTENT);
				param.gravity = Gravity.LEFT | Gravity.TOP;
				param.setMargins(msg.getX(), msg.getY(), 0, 0);
				parent.addView(button, param);
				
				msg.setSuccess(true);
			}
		};
		runnable.syncRunOnUiThread(mActivity);
		if (msg.isSuccess()) return msg.getButtonId();
		return 0;
	}
	
	// game thread
	public static void destroyButton(int viewId, int buttonId)
	{
		BaseView view = mViewMap.get(viewId);
		if (view == null) return;
		
		MsgDestroyButton msg = new MsgDestroyButton(mActivity, buttonId);
		MessageRunnable runnable = new MessageRunnable(msg)
		{
			@Override
			public void runOnUiThread()
			{
				MsgDestroyButton msg = (MsgDestroyButton)getMsg();
				Activity activity = msg.getActivity();
				
		 		FrameLayout parent = (FrameLayout)activity.findViewById(R.id.frameLayout1);
				if (parent == null) return;

				View button = parent.findViewById(msg.getButtonId());
				parent.removeView(button);
			}
		};
		runnable.syncRunOnUiThread(mActivity);
	}
	
	// game thread
	public static boolean activeView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return false;

		return view.active(mActivity);
	}
	
	// game thread
	public static boolean deactiveView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return false;
		
		view.deactive(mActivity);
		return true;
	}
	
	// game thread
	public static void destroyView(int id)
	{
		BaseView view = mViewMap.get(id);
		if (view == null) return;
		
		mViewMap.remove(id);
		view = null;
	}
	
	// game thread
	private static int genNextViewId()
	{
		return mGenViewId++;
	}
	
	private static int genNextControlId()
	{
		return mGenControlId++;
	}
	
	public static void request(MsgBase msg)
	{
		if (mRunnable != null) mRunnable.request(msg);
	}
	
	// game thread
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
	
	// game thread
	public static void terminateRenderer()
	{
		if (mRenderer != null)
		{
			mRenderer.terminateRenderer();
			mRenderer = null;
		}
	}

	// game thread
	public static void renderIfNessary()
	{
		if (mRenderer != null)
		{
			mRenderer.BeginRender();
			render();
			mRenderer.EndRender();
		}
	}
	
	// game thread
	public static native boolean initialize(String zipFilePath, int surfaceWidth, int surfaceHeight);
	public static native void terminate();
	public static native void update();
	public static native void render();

	// ui thread
	public static native void touchBegin(int index, float x, float y);
	public static native void touchMove(int index, float x, float y);
	public static native void touchEnd(int index, float x, float y);
	public static native void onKeyReturn();
	public static native void onKeyHome();
}
