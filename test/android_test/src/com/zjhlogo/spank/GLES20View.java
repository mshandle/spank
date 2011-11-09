package com.zjhlogo.spank;

import android.app.Activity;
import android.graphics.PixelFormat;
import android.view.MotionEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.view.View.OnTouchListener;

public class GLES20View extends BaseView implements SurfaceHolder.Callback, OnTouchListener
{
	public GLES20View()
	{
		super(R.layout.layout_opengles_20);
	}

	@Override
	public boolean activeOnUiThread(Activity activity)
	{
		View view = activity.getLayoutInflater().inflate(getLayoutId(), null, false);
		activity.setContentView(view);

		SurfaceView surfaceView = (SurfaceView) activity.findViewById(R.id.surfaceView1);
		if (surfaceView == null) return false;

		surfaceView.setOnTouchListener(this);
		
		SurfaceHolder holder = surfaceView.getHolder();
		if (holder == null) return false;

		// set holder pixel format
		holder.setFormat(PixelFormat.TRANSLUCENT);
		holder.addCallback(this);

		return true;
	}

	@Override
	public void deactiveOnUiThread(Activity activity)
	{
		activity.setContentView(R.layout.layout_empty);
		unblockThread();
	}

	@Override
	public boolean activeOnGameThread(Activity activity)
	{
		SurfaceView surfaceView = (SurfaceView) activity.findViewById(R.id.surfaceView1);
		if (surfaceView == null) return false;

		SurfaceHolder holder = surfaceView.getHolder();
		if (holder == null) return false;

		return SpankLibrary.initializeRenderer(holder);
	}
	
	@Override
	public void deactiveOnGameThread(Activity activity)
	{
		SpankLibrary.terminateRenderer();
	}

	public void surfaceCreated(SurfaceHolder holder)
	{
		unblockThread();
	}

	public void surfaceChanged(SurfaceHolder holder, int format, int width, int height)
	{
		// nothing to do
	}

	public void surfaceDestroyed(SurfaceHolder holder)
	{
		// TODO: send message to game thread to deactive the renderer
	}

	public boolean onTouch(View v, MotionEvent event)
	{
		switch (event.getAction())
		{
		case MotionEvent.ACTION_DOWN:
			{
				SpankLibrary.touchBegin(0, event.getX(), event.getY());
			}
			break;
		case MotionEvent.ACTION_MOVE:
			{
				SpankLibrary.touchMove(0, event.getX(), event.getY());
			}
			break;
		case MotionEvent.ACTION_UP:
		case MotionEvent.ACTION_CANCEL:
			{
				SpankLibrary.touchEnd(0, event.getX(), event.getY());
			}
			break;
		}

		return true;
	}
}
