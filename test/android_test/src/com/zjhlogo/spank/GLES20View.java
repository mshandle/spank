package com.zjhlogo.spank;

import android.app.Activity;
import android.view.SurfaceHolder;
import android.view.SurfaceView;

import com.zjhlogo.spank.msg.MSG_ID;
import com.zjhlogo.spank.msg.MsgCommand;
import com.zjhlogo.spank.msg.MsgRequestSetupRenderer;

public class GLES20View extends BaseView
{
	private SurfaceView mSurfaceView = null;
	
	public GLES20View(int resId)
	{
		super(resId);
	}

	@Override
	public boolean active(Activity activity)
	{
		if (!super.active(activity)) return false;
		
		mSurfaceView = (SurfaceView) activity.findViewById(R.id.surfaceView1);
		if (mSurfaceView == null) return false;

		SurfaceHolder holder = mSurfaceView.getHolder();
		if (holder == null) return false;
		
		// request setup renderer
		MsgRequestSetupRenderer rsr = new MsgRequestSetupRenderer(holder);
		SpankLibrary.request(rsr);
		
		return true;
	}

	@Override
	public void deactive(Activity activity)
	{
		// request uninstall renderer
		SpankLibrary.request(new MsgCommand(MSG_ID.MI_REQUEST_STOP_RENDERER));
		
		super.deactive(activity);
	}
}
