/*!
 * \file OSUISystem_Android_Impl.cpp
 * \date 11-11-2011 14:28:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "OSUISystem_Android_Impl.h"
#include <jni.h>

extern JNIEnv* g_pEnv;
extern jclass g_Class;

IOSUISystem& IOSUISystem::GetInstance()
{
	static OSUISystem_Android_Impl s_OSUISystem_Android_Impl;
	return s_OSUISystem_Android_Impl;
}

OSUISystem_Android_Impl::OSUISystem_Android_Impl()
{
	// TODO: 
}

OSUISystem_Android_Impl::~OSUISystem_Android_Impl()
{
	// TODO: 
}

bool OSUISystem_Android_Impl::Initialize()
{
	// TODO: 
	return true;
}

void OSUISystem_Android_Impl::Terminate()
{
	// TODO: 
}

int OSUISystem_Android_Impl::CreateButton(ISurfaceView* pSurfaceView, int x, int y, int width, int height, const char* pszText)
{
	int nViewId = pSurfaceView->GetViewId();

	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "createButton", "(IIIIILjava/lang/String;)I");
	return g_pEnv->CallStaticIntMethod(g_Class, mid, nViewId, x, y, width, height, g_pEnv->NewStringUTF(pszText));
}

int OSUISystem_Android_Impl::CreateEditText(ISurfaceView* pSurfaceView, int x, int y, int width, int height)
{
	int nViewId = pSurfaceView->GetViewId();

	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "createEditText", "(IIIII)I");
	return g_pEnv->CallStaticIntMethod(g_Class, mid, nViewId, x, y, width, height);
}

void OSUISystem_Android_Impl::DestroyControl(ISurfaceView* pSurfaceView, int nId)
{
	int nViewId = pSurfaceView->GetViewId();

	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "destroyControl", "(II)V");
	g_pEnv->CallStaticVoidMethod(g_Class, mid, nViewId, nId);
}
