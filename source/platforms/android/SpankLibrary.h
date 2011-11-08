/*!
 * \file SpankLibrary.h
 * \date 11-04-2011 13:27:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SPANKLIBRARY_H__
#define __SPANKLIBRARY_H__

class SpankLibrary
{
public:
	static int CreateNormalView();
	static int CreateOpenGLView();
	static bool ActiveView(int nViewId);
	static bool DeactiveView(int nViewId);
	static void DestroyView(int nViewId);

};
#endif // __SPANKLIBRARY_H__
