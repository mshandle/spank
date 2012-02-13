/*!
 * \file DesignerApp.h
 * \date 2-14-2012 1:21:20
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DESIGNERAPP_H__
#define __DESIGNERAPP_H__

#include <wx/app.h>
#include <wx/image.h>

class DesignerApp : public wxApp
{
public:
	DesignerApp();
	virtual ~DesignerApp();

	virtual bool OnInit();

};
#endif // __DESIGNERAPP_H__
