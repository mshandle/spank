/*!
 * \file AndroidMain.cpp
 * \date 24-07-2011 15:44:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "AndroidMain.h"
#include <ICore.h>
#include <util/ConfigUtil.h>
#include <util/ScreenUtil.h>
#include <util/IDebugUtil.h>
#include <InputMgr.h>
#include <msg/MsgMgr.h>
#include <time.h>

static bool g_bFirstStep = true;
static uint g_nCurrTime = 0;
static uint g_nPrevTime = 0;

JavaVM* g_pJavaVM = NULL;
JNIEnv* g_pEnv = NULL;
jclass g_Class = NULL;

static uint GetCurrTime()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return now.tv_sec*1000 + now.tv_nsec/1000000;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
	g_pJavaVM = vm;
	return JNI_VERSION_1_4;
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    initialize
 * Signature: (Ljava/lang/String;II)Z
 */
JNIEXPORT jboolean JNICALL Java_com_zjhlogo_spank_SpankLibrary_initialize(JNIEnv* env, jclass cls, jstring zipFilePath, jint width, jint height)
{
	g_pEnv = env;
	g_Class = cls;

	ConfigUtil::GetInstance().AddInt("SURFACE_WIDTH", width);
	ConfigUtil::GetInstance().AddInt("SURFACE_HEIGHT", height);

	jboolean isCopy = JNI_FALSE;
	const char* pszPath = env->GetStringUTFChars(zipFilePath, &isCopy);
	if (isCopy == JNI_TRUE)
	{
		ConfigUtil::GetInstance().AddString("ANDROID_RESOURCE_PACKAGE", pszPath);
		ConfigUtil::GetInstance().AddString("RESOURCE_DIR", "assets/");
		env->ReleaseStringUTFChars(zipFilePath, pszPath);
	}

	if (!ICore::GetInstance().Initialize())
	{
		LOGD("initialize failed with surface size %dx%d", width, height);
		return JNI_FALSE;
	}

	LOGD("initialize ok, surface size %dx%d", width, height);
	g_bFirstStep = true;
	return JNI_TRUE;
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    terminate
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_terminate(JNIEnv* env, jclass cls)
{
	LOGD("spank terminated");
	ICore::GetInstance().Terminate();
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    update
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_update(JNIEnv* env, jclass cls)
{
	if (g_bFirstStep)
	{
		g_nCurrTime = GetCurrTime();
		g_nPrevTime = g_nCurrTime;
		g_bFirstStep = false;
	}
	else
	{
		g_nCurrTime = GetCurrTime();
	}

	ICore::GetInstance().Update((g_nCurrTime - g_nPrevTime)/1000.0f);

	g_nPrevTime = g_nCurrTime;
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    render
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_render(JNIEnv* env, jclass cls)
{
	ICore::GetInstance().Render();
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    touchBegin
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchBegin(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, x, y);
	InputMgr::GetInstance().OnTouchStart(index, vPos.x, vPos.y);
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    touchMove
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchMove(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, x, y);
	InputMgr::GetInstance().OnTouchMove(index, vPos.x, vPos.y);
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    touchEnd
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchEnd(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, x, y);
	InputMgr::GetInstance().OnTouchEnd(index, vPos.x, vPos.y);
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    onKeyReturn
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_onKeyReturn(JNIEnv* env, jclass cls)
{
	InputMgr::GetInstance().OnKeyReturn();
}

/*
 * Class:     com_zjhlogo_spank_SpankLibrary
 * Method:    onKeyHome
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_onKeyHome(JNIEnv* env, jclass cls)
{
	InputMgr::GetInstance().OnKeyHome();
}
