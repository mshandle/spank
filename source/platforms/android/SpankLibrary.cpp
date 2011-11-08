/*!
 * \file SpankLibrary.cpp
 * \date 11-04-2011 13:29:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SpankLibrary.h"
#include <jni.h>

extern JNIEnv* g_pEnv;
extern jclass g_Class;

int SpankLibrary::CreateNormalView()
{
	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "createNormalView", "()I");
	int nViewId = g_pEnv->CallStaticIntMethod(g_Class, mid);
	return nViewId;
}

int SpankLibrary::CreateOpenGLView()
{
	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "createOpenGLView", "()I");
	int nViewId = g_pEnv->CallStaticIntMethod(g_Class, mid);
	return nViewId;
}

bool SpankLibrary::ActiveView(int nViewId)
{
	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "activeView", "(I)Z");
	bool bOk = g_pEnv->CallStaticBooleanMethod(g_Class, mid, nViewId);
	return bOk;
}

bool SpankLibrary::DeactiveView(int nViewId)
{
	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "deactiveView", "(I)Z");
	bool bOk = g_pEnv->CallStaticBooleanMethod(g_Class, mid, nViewId);
	return bOk;
}

void SpankLibrary::DestroyView(int nViewId)
{
	jmethodID mid = g_pEnv->GetStaticMethodID(g_Class, "destroyView", "(I)V");
	g_pEnv->CallStaticVoidMethod(g_Class, mid, nViewId);
}
