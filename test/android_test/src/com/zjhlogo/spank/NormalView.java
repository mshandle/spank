package com.zjhlogo.spank;

import android.app.Activity;
import android.view.View;

public class NormalView extends BaseView
{
	public NormalView()
	{
		super(R.layout.layout_normal);
	}
	
	@Override
	public boolean activeOnUiThread(Activity activity)
	{
		View view = activity.getLayoutInflater().inflate(getLayoutId(), null, false);
		activity.setContentView(view);
		unblockThread();
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
		return true;
	}
	
	@Override
	public void deactiveOnGameThread(Activity activity)
	{
		
	}
}
