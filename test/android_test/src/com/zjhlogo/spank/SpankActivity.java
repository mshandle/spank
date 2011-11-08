package com.zjhlogo.spank;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

public class SpankActivity extends Activity
{
	public static final int REQUEST_ACTIVE_VIEW = 1;
	public static final int REQUEST_DEACTIVE_VIEW = 2;
	
	private Handler mHandler = null;
	
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        
        mHandler = new Handler()
        {
    		public void handleMessage(Message msg)
    		{
    			switch (msg.what)
    			{
    			case REQUEST_ACTIVE_VIEW:
    			{
    				BaseView view = (BaseView) msg.obj;
    				view.active(SpankActivity.this);
       				view.Unlock();
    			}
    			break;
    			case REQUEST_DEACTIVE_VIEW: {
    				BaseView view = (BaseView) msg.obj;
    				view.deactive(SpankActivity.this);
       				view.Unlock();
    			}
    			break;
    			}
    		}
        };
        
        SpankLibrary.startApp(this, mHandler);
    }

	@Override
	protected void onDestroy()
	{
		SpankLibrary.stopApp();
		super.onDestroy();
	}

	@Override
	public void onBackPressed()
	{
		SpankLibrary.onKeyReturn();
	}
}
