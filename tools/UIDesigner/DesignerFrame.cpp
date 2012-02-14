/*!
 * \file DesignerFrame.cpp
 * \date 2-14-2012 1:22:04
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DesignerFrame.h"
#include <wx/menu.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/treectrl.h>
#include <wx/filedlg.h>

#include "document/ProjectDocument.h"
#include "document/ImagePieceDocument.h"
#include "transformer/ImageListTransformer.h"
#include "transformer/PieceListTransformer.h"
#include "transformer/BitmapStyleTransformer.h"
#include "transformer/NineGridStyleTransformer.h"
#include "transformer/ColorStyleTransformer.h"
#include "transformer/ClipBitmapStyleTransformer.h"
#include "editor/ImagePieceEditor.h"

#include "images/disk.xpm"
#include "images/document.xpm"
#include "images/document_plus.xpm"
#include "images/folder_horizontal_open.xpm"
#include "images/zoom.xpm"
#include "images/zoom_in.xpm"
#include "images/zoom_out.xpm"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

BEGIN_EVENT_TABLE(DesignerFrame, wxFrame)
	EVT_MENU(wxID_OPEN, DesignerFrame::OnFileOpen)
	EVT_MENU(wxID_SAVE, DesignerFrame::OnFileSave)
	EVT_MENU(wxID_CLOSE, DesignerFrame::OnFileClose)
	EVT_MENU(wxID_EXIT, DesignerFrame::OnExit)

	EVT_MENU(wxID_ZOOM_100, DesignerFrame::OnViewZoom100)
	EVT_MENU(wxID_ZOOM_IN, DesignerFrame::OnViewZoomIn)
	EVT_MENU(wxID_ZOOM_OUT, DesignerFrame::OnViewZoomOut)

	EVT_TREE_SEL_CHANGED(IDC_PIECE_LIST, DesignerFrame::OnImagePieceListSelected)
	EVT_TREE_SEL_CHANGED(IDC_IMAGE_LIST, DesignerFrame::OnImageListSelected)
	EVT_TREE_SEL_CHANGED(IDC_BITMAP_STYLE_LIST, DesignerFrame::OnBitmapStyleListSelected)
	EVT_TREE_SEL_CHANGED(IDC_NINE_GRID_STYLE_LIST, DesignerFrame::OnNineGridStyleListSelected)
	EVT_TREE_SEL_CHANGED(IDC_COLOR_STYLE_LIST, DesignerFrame::OnColorStyleListSelected)
	EVT_TREE_SEL_CHANGED(IDC_CLIP_BITMAP_STYLE_LIST, DesignerFrame::OnClipBitmapStyleListSelected)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(DesignerFrame, wxFrame)

DesignerFrame* DesignerFrame::m_pDesignerFrame = NULL;

DesignerFrame::DesignerFrame()
:wxFrame(NULL, wxID_ANY, wxT("UI Designer"), wxDefaultPosition, wxSize(800, 600))
{
	m_pDesignerFrame = this;
	CreateControls();
}

DesignerFrame::~DesignerFrame()
{
	m_auiManager.UnInit();
	m_pDesignerFrame = NULL;
}

DesignerFrame& DesignerFrame::GetInstance()
{
	return *m_pDesignerFrame;
}

void DesignerFrame::Init()
{
	// TODO: 
}

void DesignerFrame::CreateControls()
{
	m_auiManager.SetManagedWindow(this);

	CreateMenu();
	CreateToolbar();
	CreateListView();
	CreatePropertyView();
	CreateEditorView();
	CreateOutputView();

	m_auiManager.Update();
}

void DesignerFrame::CreateMenu()
{
	wxMenuBar* pMenuBar = new wxMenuBar();

	// file
	wxMenu* pMenuItemFile = new wxMenu();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, wxID_OPEN, wxT("&Open...\tCtrl+O"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(folder_horizontal_open_xpm, wxBITMAP_TYPE_XPM);
		menuItem->SetBitmap(bitmap);
		pMenuItemFile->Append(menuItem);
	}
	pMenuItemFile->AppendSeparator();
	pMenuItemFile->Append(wxID_CLOSE, wxT("&Close"), wxEmptyString, wxITEM_NORMAL);

	pMenuItemFile->AppendSeparator();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, wxID_SAVE, wxT("&Save\tCtrl+S"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(disk_xpm, wxBITMAP_TYPE_XPM);
		menuItem->SetBitmap(bitmap);
		pMenuItemFile->Append(menuItem);
	}

	pMenuItemFile->Append(wxID_SAVEAS, wxT("Save &As...\tCtrl+Shift+S"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemFile->AppendSeparator();
	pMenuItemFile->Append(wxID_EXIT, wxT("E&xit\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemFile, wxT("&File"));


	// edit
	wxMenu* pMenuItemEdit = new wxMenu();
	pMenuItemEdit->Append(IDM_EDIT_UNDO, wxT("&Undo\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(IDM_EDIT_REDO, wxT("&Redo\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->AppendSeparator();
	pMenuItemEdit->Append(IDM_EDIT_COPY, wxT("&Copy\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(IDM_EDIT_CUT, wxT("Cu&t\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(IDM_EDIT_PAST, wxT("&Past\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(IDM_EDIT_DELETE, wxT("&Delete\tDel"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemEdit, wxT("&Edit"));

	// view
	wxMenu* pMenuItemView = new wxMenu();
	pMenuItemView->Append(IDM_VIEW_GRID, wxT("Show &Grid\tCtrl+G"), wxEmptyString, wxITEM_CHECK);
	pMenuItemView->Check(IDM_VIEW_GRID, true);
	pMenuItemView->AppendSeparator();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, wxID_ZOOM_100, wxT("Zoom &100%\tCtrl+1"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(zoom_xpm, wxBITMAP_TYPE_XPM);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, wxID_ZOOM_IN, wxT("Zoom &In\tCtrl++"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(zoom_in_xpm, wxBITMAP_TYPE_XPM);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, wxID_ZOOM_OUT, wxT("Zoom &Out\tCtrl+-"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(zoom_out_xpm, wxBITMAP_TYPE_XPM);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	pMenuBar->Append(pMenuItemView, wxT("&View"));

	// tool
	wxMenu* pMenuItemTool = new wxMenu();
	pMenuItemTool->Append(IDM_TOOL_PREFERENCES, wxT("&Preferences..."), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemTool, wxT("&Tools"));

	// help
	wxMenu* pMenuItemHelp = new wxMenu();
	pMenuItemHelp->Append(IDM_HELP_SUPPORT, wxT("&Support"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemHelp->AppendSeparator();
	pMenuItemHelp->Append(IDM_HELP_ABOUT, wxT("&About\tF1"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemHelp, wxT("&Help"));

	SetMenuBar(pMenuBar);
}

void DesignerFrame::CreateToolbar()
{
	wxAuiToolBar* pAuiToolBar = new wxAuiToolBar(this, IDC_TOOLBAR, wxDefaultPosition, wxDefaultSize, 0);

	{
		wxBitmap bitmap(document_plus_xpm, wxBITMAP_TYPE_XPM);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_NEW, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(folder_horizontal_open_xpm, wxBITMAP_TYPE_XPM);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_OPEN, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(disk_xpm, wxBITMAP_TYPE_XPM);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_SAVE, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	pAuiToolBar->AddSeparator();

	{
		wxBitmap bitmap(zoom_xpm, wxBITMAP_TYPE_XPM);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_ZOOM_100, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(zoom_in_xpm, wxBITMAP_TYPE_XPM);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_ZOOM_IN, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(zoom_out_xpm, wxBITMAP_TYPE_XPM);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_ZOOM_OUT, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	pAuiToolBar->Realize();

	m_auiManager.AddPane(pAuiToolBar, wxAuiPaneInfo()
		.Name(wxT("Toolbar"))
		.Top()
		.Layer(1)
		.Dockable(false)
		.CaptionVisible(false)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.Movable(false)
		.PaneBorder(false));
}

void DesignerFrame::CreateListView()
{
	wxNotebook* pNotebookView = new wxNotebook(this, IDC_NOTEBOOK_EDITOR, wxDefaultPosition, wxDefaultSize, wxNB_MULTILINE|wxNO_BORDER);
	m_auiManager.AddPane(pNotebookView, wxAuiPaneInfo()
		.Name(wxT("List"))
		.Caption(wxT("List"))
		.Left()
		.Layer(1)
		.BestSize(wxSize(400, 500))
		.CaptionVisible(true)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(400, 500))
		.Movable(false));

	wxTreeCtrl* pImagePieceListView = new wxTreeCtrl(pNotebookView, IDC_PIECE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pImagePieceListView, "Pieces");
	PieceListTransformer::GetInstance().Initialize(pImagePieceListView);

	wxTreeCtrl* pImageListView = new wxTreeCtrl(pNotebookView, IDC_IMAGE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pImageListView, "Images");
	ImageListTransformer::GetInstance().Initialize(pImageListView);

	wxTreeCtrl* pBitmapStyleListView = new wxTreeCtrl(pNotebookView, IDC_BITMAP_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pBitmapStyleListView, "Bitmap Styles");
	BitmapStyleTransformer::GetInstance().Initialize(pBitmapStyleListView);

	wxTreeCtrl* pNineGridStyleListView = new wxTreeCtrl(pNotebookView, IDC_NINE_GRID_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pNineGridStyleListView, "9-Grid Styles");
	NineGridStyleTransformer::GetInstance().Initialize(pNineGridStyleListView);

	wxTreeCtrl* pColorStyleListView = new wxTreeCtrl(pNotebookView, IDC_COLOR_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pColorStyleListView, "Color Styles");
	ColorStyleTransformer::GetInstance().Initialize(pColorStyleListView);

	wxTreeCtrl* pClipBitmapStyleListView = new wxTreeCtrl(pNotebookView, IDC_CLIP_BITMAP_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pClipBitmapStyleListView, "Clip Bitmap Styles");
	ClipBitmapStyleTransformer::GetInstance().Initialize(pClipBitmapStyleListView);
}

void DesignerFrame::CreatePropertyView()
{
	m_pPropertyGrid = new wxPropertyGrid(this, IDC_PROPERTY, wxDefaultPosition, wxDefaultSize, wxPG_SPLITTER_AUTO_CENTER|wxNO_BORDER);
	m_auiManager.AddPane(m_pPropertyGrid, wxAuiPaneInfo()
		.Name(wxT("Property"))
		.Caption(wxT("Property"))
		.Right()
		.BestSize(wxSize(300, 300))
		.Position(1)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(300, 500))
		.Movable(false));
}

void DesignerFrame::CreateEditorView()
{
	wxNotebook* pNotebookView = new wxNotebook(this, IDC_NOTEBOOK_EDITOR, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_auiManager.AddPane(pNotebookView, wxAuiPaneInfo()
		.Name(wxT("Editor"))
		.Caption(wxT("Editor"))
		.Centre()
		.CaptionVisible(false)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.Movable(false));

	ImagePieceEditor* pImagePieceEditor = new ImagePieceEditor(pNotebookView, IDC_EDITOR_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	pNotebookView->AddPage(pImagePieceEditor, "Pieces Editor");
}

void DesignerFrame::CreateOutputView()
{
	m_pOutputView = new wxTextCtrl(this, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_READONLY|wxTE_MULTILINE|wxNO_BORDER);
	m_pOutputView->AppendText(wxT("This is output view\n"));
	m_pOutputView->AppendText(wxT("line 1\n"));
	m_pOutputView->AppendText(wxT("line 2\n"));

	m_auiManager.AddPane(m_pOutputView, wxAuiPaneInfo()
		.Name(wxT("Output"))
		.Caption(wxT("Output"))
		.Bottom()
		.BestSize(wxSize(300, 300))
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(500, 200))
		.Movable(false));
}

void DesignerFrame::OnFileOpen(wxCommandEvent& event)
{
	wxFileDialog dialog(this, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("Project files (*.udproj)|*.udproj"), wxFD_DEFAULT_STYLE);
	if (dialog .ShowModal() == wxID_OK)
	{
		wxString strPath = dialog.GetPath();
		ProjectDocument::GetInstance().OpenFile(strPath);
	}
}

void DesignerFrame::OnFileSave(wxCommandEvent& event)
{
	if (!ProjectDocument::GetInstance().GetFilePath().IsEmpty())
	{
		ProjectDocument::GetInstance().SaveFile(ProjectDocument::GetInstance().GetFilePath());
	}
}

void DesignerFrame::OnFileClose(wxCommandEvent& event)
{
	// TODO: 
}

void DesignerFrame::OnExit(wxCommandEvent& event)
{
	Destroy();
}

void DesignerFrame::OnViewZoom100(wxCommandEvent& event)
{
	ImagePieceEditor::GetInstance().Zoom(ImagePieceEditor::ZOOM_MIN);
}

void DesignerFrame::OnViewZoomIn(wxCommandEvent& event)
{
	ImagePieceEditor::GetInstance().ZoomIn();
}

void DesignerFrame::OnViewZoomOut(wxCommandEvent& event)
{
	ImagePieceEditor::GetInstance().ZoomOut();
}

void DesignerFrame::OnImagePieceListSelected(wxTreeEvent& event)
{
	PieceInfo* pPieceInfo = PieceListTransformer::GetInstance().GetSelectedPieceInfo();
	if (pPieceInfo)
	{
		ImageInfo* pImageInfo = ImagePieceDocument::GetInstance().FindImageInfo(pPieceInfo->GetImageId());
		ImagePieceEditor::GetInstance().SetImage(pImageInfo);
		ImageListTransformer::GetInstance().SetSelectedImageInfo(pImageInfo);
	}
	ImagePieceEditor::GetInstance().SetSelection(pPieceInfo);
}

void DesignerFrame::OnImageListSelected(wxTreeEvent& event)
{
	ImageInfo* pImageInfo = ImageListTransformer::GetInstance().GetSelectedImageInfo();
	ImagePieceEditor::GetInstance().SetImage(pImageInfo);
	ImagePieceEditor::GetInstance().SetSelection(NULL);
}

void DesignerFrame::OnBitmapStyleListSelected(wxTreeEvent& event)
{
	// TODO: 
}

void DesignerFrame::OnNineGridStyleListSelected(wxTreeEvent& event)
{
	// TODO: 
}

void DesignerFrame::OnColorStyleListSelected(wxTreeEvent& event)
{
	// TODO: 
}

void DesignerFrame::OnClipBitmapStyleListSelected(wxTreeEvent& event)
{
	// TODO: 
}
