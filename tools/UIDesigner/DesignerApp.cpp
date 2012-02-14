/*!
 * \file DesignerApp.cpp
 * \date 2-14-2012 1:21:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DesignerApp.h"
#include "DesignerFrame.h"

IMPLEMENT_APP(DesignerApp)

DesignerApp::DesignerApp()
{
	// TODO: 
}

DesignerApp::~DesignerApp()
{
	// TODO: 
}

bool DesignerApp::OnInit()
{
	wxImage::AddHandler(new wxXPMHandler());
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxJPEGHandler());
	wxImage::AddHandler(new wxCURHandler());

	DesignerFrame* mainWindow = new DesignerFrame();
	mainWindow->Maximize(true);
	mainWindow->Show(true);

	return true;
}
