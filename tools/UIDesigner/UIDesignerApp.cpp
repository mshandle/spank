/*!
 * \file UIDesignerApp.cpp
 * \date 8-31-2011 13:07:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIDesignerApp.h"
#include "UIDesignerFrame.h"

IMPLEMENT_APP(UIDesignerApp)

UIDesignerApp::UIDesignerApp()
{
	// TODO: 
}

UIDesignerApp::~UIDesignerApp()
{
	// TODO: 
}

bool UIDesignerApp::OnInit()
{
	wxImage::AddHandler(new wxPNGHandler());
	wxImage::AddHandler(new wxJPEGHandler());
	wxImage::AddHandler(new wxCURHandler());

	UIDesignerFrame* mainWindow = new UIDesignerFrame();
	mainWindow->Maximize(true);
	mainWindow->Show(true);

	return true;
}
