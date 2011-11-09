package com.zjhlogo.spank;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLContext;
import javax.microedition.khronos.egl.EGLDisplay;
import javax.microedition.khronos.egl.EGLSurface;

import android.util.Log;
import android.view.SurfaceHolder;

public class SpankRenderer {
	private static final int EGL_CONTEXT_CLIENT_VERSION = 0x3098;
	private static final int EGL_OPENGL_ES2_BIT = 4;
	private static final int BLUE_BITS = 8;
	private static final int GREEN_BITS = 8;
	private static final int RED_BITS = 8;
	private static final int ALPHA_BITS = 8;
	private static final int DEPTH_BITS = 24;
	private static final int STENCIL_BITS = 8;
	
	private static final int[] s_configAttribs2 =
	{
		EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL10.EGL_BLUE_SIZE, BLUE_BITS,
		EGL10.EGL_GREEN_SIZE, GREEN_BITS,
		EGL10.EGL_RED_SIZE, RED_BITS,
		EGL10.EGL_ALPHA_SIZE, ALPHA_BITS,
		EGL10.EGL_DEPTH_SIZE, DEPTH_BITS,
		EGL10.EGL_STENCIL_SIZE, STENCIL_BITS,
		EGL10.EGL_NONE
	};

	private EGL10 mEgl = null;
	private EGLDisplay mEglDisplay = null;
	private EGLConfig mEglConfig = null;
	private EGLContext mEglContext = null;
	private EGLSurface mEglSurface = null;
	private SurfaceHolder mHolder = null;
	
	public SpankRenderer(SurfaceHolder holder)
	{
		mHolder = holder;
	}
	
	public boolean initializeRenderer()
	{
		// initialize EGL
		mEgl = (EGL10) EGLContext.getEGL();
		
		// get the default display
		mEglDisplay = mEgl.eglGetDisplay(EGL10.EGL_DEFAULT_DISPLAY);
		if (mEglDisplay == EGL10.EGL_NO_DISPLAY)
		{
			Log.e("spank", "get the default display failed");
			return false;
		}
		
		// initialize EGL for display
		int[] version = new int[2];
		if (!mEgl.eglInitialize(mEglDisplay, version))
		{
			Log.e("spank", "initialize EGL for display failed");
			return false;
		}
		// setup config chooser
        mEglConfig = chooseConfig(mEgl, mEglDisplay);

		// create EGL context
        mEglContext = createContext(mEgl, mEglDisplay, mEglConfig);
        if (mEglContext == null || mEglContext == EGL10.EGL_NO_CONTEXT)
        {
			Log.e("spank", "create EGL context failed");
        	return false;
        }

        // create egl surface
        mEglSurface = mEgl.eglCreateWindowSurface(mEglDisplay, mEglConfig, mHolder, null);
        if (mEglSurface == null || mEglSurface == EGL10.EGL_NO_SURFACE)
        {
			Log.e("spank", "create egl surface failed: " + mEgl.eglGetError());
        	return false;
        }

        // make current context
        if (!mEgl.eglMakeCurrent(mEglDisplay, mEglSurface, mEglSurface, mEglContext))
        {
			Log.e("spank", "make current context failed");
        	return false;
        }

        return true;
	}
	
	public void terminateRenderer()
	{
        mEgl.eglMakeCurrent(mEglDisplay, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_SURFACE, EGL10.EGL_NO_CONTEXT);
        mEgl.eglDestroySurface(mEglDisplay, mEglSurface);
        mEgl.eglDestroyContext(mEglDisplay, mEglContext);
    	mEgl = null;
    	mEglDisplay = null;
    	mEglConfig = null;
    	mEglContext = null;
    	mEglSurface = null;
    	mHolder = null;
	}
	
	public void BeginRender()
	{
		// nothing to do
	}
	
	public void EndRender()
	{
		if (mEgl == null) return;
        mEgl.eglSwapBuffers(mEglDisplay, mEglSurface);
	}
	
	private EGLConfig chooseConfig(EGL10 egl, EGLDisplay display)
	{
		/*
		 * Get the number of minimally matching EGL configurations
		 */
		int[] num_config = new int[1];
		egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

		int numConfigs = num_config[0];

		if (numConfigs <= 0)
		{
			throw new IllegalArgumentException("No configs match configSpec");
		}

		/*
		 * Allocate then read the array of minimally matching EGL configs
		 */
		EGLConfig[] configs = new EGLConfig[numConfigs];
		egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

		/*
		 * Now return the "best" one
		 */
		return chooseBestConfig(egl, display, configs);
	}

	private EGLConfig chooseBestConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs)
	{
		for (EGLConfig config : configs)
		{
			int depth = findConfigAttrib(egl, display, config, EGL10.EGL_DEPTH_SIZE, 0);
			int stencil = findConfigAttrib(egl, display, config, EGL10.EGL_STENCIL_SIZE, 0);

			// We need at least mDepthSize and mStencilSize bits
			if (depth < DEPTH_BITS || stencil < STENCIL_BITS) continue;

			// We want an *exact* match for red/green/blue/alpha
			int red = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE, 0);
			int green = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
			int blue = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE, 0);
			int alpha = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);

			if (red == RED_BITS && green == GREEN_BITS && blue == BLUE_BITS && alpha == ALPHA_BITS)
			{
				return config;
			}
		}
		return null;
	}

	private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue)
	{
		int[] value = new int[1];
		if (egl.eglGetConfigAttrib(display, config, attribute, value))
		{
			return value[0];
		}
		
		return defaultValue;
	}

	private EGLContext createContext(EGL10 egl, EGLDisplay display, EGLConfig config)
	{
		int[] attrib_list = {EGL_CONTEXT_CLIENT_VERSION, 2, EGL10.EGL_NONE};
		return egl.eglCreateContext(display, config, EGL10.EGL_NO_CONTEXT, attrib_list);
	}
}
