package com.zjhlogo.spank.msg;

import android.view.SurfaceHolder;

public class MsgRequestSetupRenderer extends MsgBase {
	private SurfaceHolder mHolder = null;
	
	public MsgRequestSetupRenderer(SurfaceHolder holder) {
		super(MSG_ID.MI_REQUEST_SETUP_RENDERER);
		mHolder = holder;
	}

	public SurfaceHolder getHolder()
	{
		return mHolder;
	}
}
