package com.zjhlogo.spank;

import android.app.Activity;
import android.os.Bundle;

public class SpankActivity extends Activity
{
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        SpankLibrary.startApp(this);
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
