package com.zjhlogo.spank;

public class SpankLibrary
{
    static
    {
        System.loadLibrary("android_test");
    }

    public static native void setPackagePath(String zipFilePath);
    
    public static native boolean initialize(int width, int height);
    public static native void terminate();
    public static native void step();
}