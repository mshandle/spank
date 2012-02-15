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
#include "editor/BitmapStyleEditor.h"
#include "editor/NineGridStyleEditor.h"
#include "editor/ColorStyleEditor.h"
#include "editor/ClipBitmapStyleEditor.h"

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

	EVT_PG_CHANGED(IDC_PROPERTY, DesignerFrame::OnPropertyGridChanged)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(DesignerFrame, wxFrame)

DesignerFrame* DesignerFrame::m_pDesignerFrame = NULL;

DesignerFrame::DesignerFrame()
:wxFrame(NULL, wxID_ANY, wxT("UI Designer"), wxDefaultPosition, wxSize(800, 600))
{
	Init();
	CreateControls();
}

DesignerFrame::~DesignerFrame()
{
	Release();
}

DesignerFrame& DesignerFrame::GetInstance()
{
	return *m_pDesignerFrame;
}

void DesignerFrame::Init()
{
	m_pDesignerFrame = this;
	m_pOutputView = NULL;
	m_eCurrPropertyType = PT_UNKNOWN;
	m_pPropertyGrid = NULL;
	m_pEditorNotebook = NULL;
	memset(m_pEditors, 0, sizeof(m_pEditors));
}

void DesignerFrame::Release()
{
	m_auiManager.UnInit();
	m_pDesignerFrame = NULL;
}

void DesignerFrame::SetCurrPropertyType(PROPERTY_TYPE eType)
{
	m_eCurrPropertyType = eType;
}

DesignerFrame::PROPERTY_TYPE DesignerFrame::GetCurrPropertyType() const
{
	return m_eCurrPropertyType;
}

void DesignerFrame::CreateControls()
{
	m_auiManager.SetManagedWindow(this);

	CreateMenu();
	CreateToolbar();
	CreatePropertyView();
	CreateListView();
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
	PieceListTransformer::GetInstance().Initialize(pImagePieceListView, m_pPropertyGrid);

	wxTreeCtrl* pImageListView = new wxTreeCtrl(pNotebookView, IDC_IMAGE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pImageListView, "Images");
	ImageListTransformer::GetInstance().Initialize(pImageListView, m_pPropertyGrid);

	wxTreeCtrl* pBitmapStyleListView = new wxTreeCtrl(pNotebookView, IDC_BITMAP_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pBitmapStyleListView, "Bitmap Styles");
	BitmapStyleTransformer::GetInstance().Initialize(pBitmapStyleListView, m_pPropertyGrid);

	wxTreeCtrl* pNineGridStyleListView = new wxTreeCtrl(pNotebookView, IDC_NINE_GRID_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pNineGridStyleListView, "9-Grid Styles");
	NineGridStyleTransformer::GetInstance().Initialize(pNineGridStyleListView, m_pPropertyGrid);

	wxTreeCtrl* pColorStyleListView = new wxTreeCtrl(pNotebookView, IDC_COLOR_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pColorStyleListView, "Color Styles");
	ColorStyleTransformer::GetInstance().Initialize(pColorStyleListView, m_pPropertyGrid);

	wxTreeCtrl* pClipBitmapStyleListView = new wxTreeCtrl(pNotebookView, IDC_CLIP_BITMAP_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	pNotebookView->AddPage(pClipBitmapStyleListView, "Clip Bitmap Styles");
	ClipBitmapStyleTransformer::GetInstance().Initialize(pClipBitmapStyleListView, m_pPropertyGrid);
}

void DesignerFrame::CreateEditorView()
{
	m_pEditorNotebook = new wxNotebook(this, IDC_NOTEBOOK_EDITOR, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_auiManager.AddPane(m_pEditorNotebook, wxAuiPaneInfo()
		.Name(wxT("Editor"))
		.Caption(wxT("Editor"))
		.Centre()
		.CaptionVisible(false)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.Movable(false));

	ImagePieceEditor* pImagePieceEditor = new ImagePieceEditor(m_pEditorNotebook, IDC_IMAGE_PIECE_EDITOR_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	m_pEditorNotebook->AddPage(pImagePieceEditor, "Pieces Editor");
	m_pEditors[EDITOR_IMAGE_PIECE] = pImagePieceEditor;

	BitmapStyleEditor* pBitmapStyleEditor = new BitmapStyleEditor(m_pEditorNotebook, IDC_BITMAP_STYLE_EDITOR_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	m_pEditorNotebook->AddPage(pBitmapStyleEditor, "Bitmap Style Editor");
	m_pEditors[EDITOR_BITMAP_STYLE] = pBitmapStyleEditor;

	NineGridStyleEditor* pNineGridStyleEditor = new NineGridStyleEditor(m_pEditorNotebook, IDC_NINE_GRID_STYLE_EDITOR_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	m_pEditorNotebook->AddPage(pNineGridStyleEditor, "Nine Grid Style Editor");
	m_pEditors[EDITOR_NINE_GRID_STYLE] = pNineGridStyleEditor;

	ColorStyleEditor* pColorStyleEditor = new ColorStyleEditor(m_pEditorNotebook, IDC_COLOR_STYLE_EDITOR_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	m_pEditorNotebook->AddPage(pColorStyleEditor, "Color Style Editor");
	m_pEditors[EDITOR_COLOR_STYLE] = pColorStyleEditor;

	ClipBitmapStyleEditor* pClipBitmapStyleEditor = new ClipBitmapStyleEditor(m_pEditorNotebook, IDC_CLIP_BITMAP_STYLE_EDITOR_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	m_pEditorNotebook->AddPage(pClipBitmapStyleEditor, "Clip Bitmap Style Editor");
	m_pEditors[EDITOR_CLIP_BITMAP_STYLE] = pClipBitmapStyleEditor;
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
		wxString strDir = dialog.GetDirectory();
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
	m_pEditors[m_pEditorNotebook->GetSelection()]->Zoom(BaseEditor::ZOOM_MIN);
}

void DesignerFrame::OnViewZoomIn(wxCommandEvent& event)
{
	m_pEditors[m_pEditorNotebook->GetSelection()]->ZoomIn();
}

void DesignerFrame::OnViewZoomOut(wxCommandEvent& event)
{
	m_pEditors[m_pEditorNotebook->GetSelection()]->ZoomOut();
}

void DesignerFrame::OnImagePieceListSelected(wxTreeEvent& event)
{
	m_pEditorNotebook->SetSelection(EDITOR_IMAGE_PIECE);
	PieceInfo* pPieceInfo = PieceListTransformer::GetInstance().GetSelectedPieceInfo();
	if (pPieceInfo)
	{
		ImageInfo* pImageInfo = pPieceInfo->GetImageInfo();
		ImagePieceEditor::GetInstance().SetImage(pImageInfo);
		ImageListTransformer::GetInstance().SetSelectedImageInfo(pImageInfo);
	}
	ImagePieceEditor::GetInstance().SetSelection(pPieceInfo);
	PieceListTransformer::GetInstance().UpdateProperty(pPieceInfo);
}

void DesignerFrame::OnImageListSelected(wxTreeEvent& event)
{
	m_pEditorNotebook->SetSelection(EDITOR_IMAGE_PIECE);
	ImageInfo* pImageInfo = ImageListTransformer::GetInstance().GetSelectedImageInfo();
	ImagePieceEditor::GetInstance().SetImage(pImageInfo);
	ImagePieceEditor::GetInstance().SetSelection(NULL);
	ImageListTransformer::GetInstance().UpdateProperty(pImageInfo);
}

void DesignerFrame::OnBitmapStyleListSelected(wxTreeEvent& event)
{
	m_pEditorNotebook->SetSelection(EDITOR_BITMAP_STYLE);
	BitmapStyle* pBitmapStyle = BitmapStyleTransformer::GetInstance().GetSelectedBitmapStyle();
	BitmapStyleEditor::GetInstance().SetBitmapStyle(pBitmapStyle);
	BitmapStyleTransformer::GetInstance().UpdateProperty(pBitmapStyle);
}

void DesignerFrame::OnNineGridStyleListSelected(wxTreeEvent& event)
{
	m_pEditorNotebook->SetSelection(EDITOR_NINE_GRID_STYLE);
	NineGridStyle* pNineGridStyle = NineGridStyleTransformer::GetInstance().GetSelectedNineGridStyle();
	NineGridStyleEditor::GetInstance().SetNineGridStyle(pNineGridStyle);
	NineGridStyleTransformer::GetInstance().UpdateProperty(pNineGridStyle);
}

void DesignerFrame::OnColorStyleListSelected(wxTreeEvent& event)
{
	m_pEditorNotebook->SetSelection(EDITOR_COLOR_STYLE);
	ColorStyle* pColorStyle = ColorStyleTransformer::GetInstance().GetSelectedColorStyle();
	ColorStyleEditor::GetInstance().SetColorStyle(pColorStyle);
	ColorStyleTransformer::GetInstance().UpdateProperty(pColorStyle);
}

void DesignerFrame::OnClipBitmapStyleListSelected(wxTreeEvent& event)
{
	m_pEditorNotebook->SetSelection(EDITOR_CLIP_BITMAP_STYLE);
	ClipBitmapStyle* pClipBitmapStyle = ClipBitmapStyleTransformer::GetInstance().GetSelectedClipBitmapStyle();
	ClipBitmapStyleEditor::GetInstance().SetClipBitmapStyle(pClipBitmapStyle);
	ClipBitmapStyleTransformer::GetInstance().UpdateProperty(pClipBitmapStyle);
}

void DesignerFrame::OnPropertyGridChanged(wxPropertyGridEvent& event)
{
	wxPGProperty* pProperty = event.GetProperty();

	switch (m_eCurrPropertyType)
	{
	case PT_IMAGE:
		ImageListTransformer::GetInstance().PropertyChanged(pProperty);
		break;
	case PT_PIECE:
		PieceListTransformer::GetInstance().PropertyChanged(pProperty);
		break;
	case PT_BITMAP_STYLE:
		BitmapStyleTransformer::GetInstance().PropertyChanged(pProperty);
		break;
	case PT_NINE_GRID_STYLE:
		NineGridStyleTransformer::GetInstance().PropertyChanged(pProperty);
		break;
	case PT_COLOR_STYLE:
		ColorStyleTransformer::GetInstance().PropertyChanged(pProperty);
		break;
	case PT_CLIP_BITMAP_STYLE:
		ClipBitmapStyleTransformer::GetInstance().PropertyChanged(pProperty);
		break;
	}
}