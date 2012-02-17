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
#include <wx/textdlg.h>

#include "document/ProjectDocument.h"
#include "document/ImagePieceDocument.h"
#include "document/BitmapStyleDocument.h"
#include "document/NineGridStyleDocument.h"
#include "document/ColorStyleDocument.h"
#include "document/ClipBitmapStyleDocument.h"

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

#include "dialog/DialogAddPiece.h"
#include "utils/FileUtil.h"

#include "images/disk.xpm"
#include "images/document.xpm"
#include "images/document_plus.xpm"
#include "images/folder_horizontal_open.xpm"
#include "images/zoom.xpm"
#include "images/zoom_in.xpm"
#include "images/zoom_out.xpm"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

BEGIN_EVENT_TABLE(DesignerFrame, wxFrame)
	EVT_CLOSE(DesignerFrame::OnClose)

	EVT_MENU(wxID_OPEN, DesignerFrame::OnFileOpen)
	EVT_MENU(wxID_SAVE, DesignerFrame::OnFileSave)
	EVT_MENU(wxID_EXIT, DesignerFrame::OnFileExit)

	EVT_MENU(IDM_EDIT_DELETE, DesignerFrame::OnEditDelete)

	EVT_MENU(IDM_ELEMENT_ADD_PIECE, DesignerFrame::OnAddPiece)
	EVT_MENU(IDM_ELEMENT_ADD_BITMAP_STYLE, DesignerFrame::OnAddBitmapStyle)
	EVT_MENU(IDM_ELEMENT_ADD_NINE_GRID_STYLE, DesignerFrame::OnAddNineGridStyle)
	EVT_MENU(IDM_ELEMENT_ADD_COLOR_STYLE, DesignerFrame::OnAddColorStyle)
	EVT_MENU(IDM_ELEMENT_ADD_CLIP_BITMAP_STYLE, DesignerFrame::OnAddClipBitmapStyle)

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
	m_pListNotebook = NULL;
	m_pEditorNotebook = NULL;
	m_eCurrEditor = NUM_EDITOR;
	memset(m_pEditors, 0, sizeof(m_pEditors));
	m_bTitleModifiedFlag = false;
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

void DesignerFrame::UpdateTitle(bool bModified, bool bForce /* = false */)
{
	if (!bForce && m_bTitleModifiedFlag == bModified) return;
	m_bTitleModifiedFlag = bModified;
	if (m_bTitleModifiedFlag)
	{
		SetTitle(FileUtil::GetFileName(ProjectDocument::GetInstance().GetFilePath()) + wxT(" *"));
	}
	else
	{
		SetTitle(FileUtil::GetFileName(ProjectDocument::GetInstance().GetFilePath()));
	}
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
	pMenuItemEdit->Append(IDM_EDIT_DELETE, wxT("&Delete\tCtrl+D"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemEdit, wxT("&Edit"));

	// elements
	wxMenu* pMenuItemElement = new wxMenu();
	pMenuItemElement->Append(IDM_ELEMENT_ADD_PIECE, wxT("Add &Piece"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemElement->Append(IDM_ELEMENT_ADD_BITMAP_STYLE, wxT("Add &Bitmap Style"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemElement->Append(IDM_ELEMENT_ADD_NINE_GRID_STYLE, wxT("Add 9-&Grid Style"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemElement->Append(IDM_ELEMENT_ADD_COLOR_STYLE, wxT("Add &Color Style"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemElement->Append(IDM_ELEMENT_ADD_CLIP_BITMAP_STYLE, wxT("Add C&lip Bitmap Style"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemElement, wxT("E&lement"));

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

// 	{
// 		wxBitmap bitmap(document_plus_xpm, wxBITMAP_TYPE_XPM);
// 		wxBitmap bitmapDisabled;
// 		pAuiToolBar->AddTool(wxID_NEW, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
// 	}

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
	m_pListNotebook = new wxNotebook(this, IDC_NOTEBOOK_EDITOR, wxDefaultPosition, wxDefaultSize, wxNB_MULTILINE|wxNO_BORDER);
	m_auiManager.AddPane(m_pListNotebook, wxAuiPaneInfo()
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

	wxTreeCtrl* pImagePieceListView = new wxTreeCtrl(m_pListNotebook, IDC_PIECE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pListNotebook->AddPage(pImagePieceListView, "Pieces");
	PieceListTransformer::GetInstance().Initialize(pImagePieceListView, m_pPropertyGrid);

	wxTreeCtrl* pImageListView = new wxTreeCtrl(m_pListNotebook, IDC_IMAGE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pListNotebook->AddPage(pImageListView, "Images");
	ImageListTransformer::GetInstance().Initialize(pImageListView, m_pPropertyGrid);

	wxTreeCtrl* pBitmapStyleListView = new wxTreeCtrl(m_pListNotebook, IDC_BITMAP_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pListNotebook->AddPage(pBitmapStyleListView, "Bitmap Styles");
	BitmapStyleTransformer::GetInstance().Initialize(pBitmapStyleListView, m_pPropertyGrid);

	wxTreeCtrl* pNineGridStyleListView = new wxTreeCtrl(m_pListNotebook, IDC_NINE_GRID_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pListNotebook->AddPage(pNineGridStyleListView, "9-Grid Styles");
	NineGridStyleTransformer::GetInstance().Initialize(pNineGridStyleListView, m_pPropertyGrid);

	wxTreeCtrl* pColorStyleListView = new wxTreeCtrl(m_pListNotebook, IDC_COLOR_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pListNotebook->AddPage(pColorStyleListView, "Color Styles");
	ColorStyleTransformer::GetInstance().Initialize(pColorStyleListView, m_pPropertyGrid);

	wxTreeCtrl* pClipBitmapStyleListView = new wxTreeCtrl(m_pListNotebook, IDC_CLIP_BITMAP_STYLE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pListNotebook->AddPage(pClipBitmapStyleListView, "Clip Bitmap Styles");
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
	if (IsModified())
	{
		wxMessageDialog dialog(this, wxT("Save Project ?"), wxT("Do you want to save the Project ?"), wxYES_NO|wxCANCEL);
		switch (dialog .ShowModal())
		{
		case wxID_YES:
			DoSaveFile();
			break;
		case wxID_NO:
			DoOpenFile();
			break;
		case wxID_CANCEL:
			break;
		}
	}
	else
	{
		DoOpenFile();
	}
}

void DesignerFrame::DoOpenFile()
{
	wxFileDialog dialog(this, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("Project files (*.udproj)|*.udproj"), wxFD_DEFAULT_STYLE);
	if (dialog .ShowModal() == wxID_OK)
	{
		wxString strPath = dialog.GetPath();
		wxString strDir = dialog.GetDirectory();
		ProjectDocument::GetInstance().SetProjectDir(strDir);
		if (ProjectDocument::GetInstance().OpenFile(strPath))
		{
			ImagePieceDocument::GetInstance().OpenFile(ProjectDocument::GetInstance().GetImagePieceFilePath());
			BitmapStyleDocument::GetInstance().OpenFile(ProjectDocument::GetInstance().GetBitmapStyleFilePath());
			NineGridStyleDocument::GetInstance().OpenFile(ProjectDocument::GetInstance().GetNineGridStyleFilePath());
			ColorStyleDocument::GetInstance().OpenFile(ProjectDocument::GetInstance().GetColorStyleFilePath());
			ClipBitmapStyleDocument::GetInstance().OpenFile(ProjectDocument::GetInstance().GetClipBitmapStyleFilePath());

			ImageListTransformer::GetInstance().UpdateListView();
			PieceListTransformer::GetInstance().UpdateListView();
			BitmapStyleTransformer::GetInstance().UpdateListView();
			NineGridStyleTransformer::GetInstance().UpdateListView();
			ColorStyleTransformer::GetInstance().UpdateListView();
			ClipBitmapStyleTransformer::GetInstance().UpdateListView();

			UpdateTitle(IsModified(), true);
		}
	}
}

void DesignerFrame::OnFileSave(wxCommandEvent& event)
{
	DoSaveFile();
}

void DesignerFrame::DoSaveFile()
{
	ProjectDocument::GetInstance().SaveFile(ProjectDocument::GetInstance().GetFilePath());
	ImagePieceDocument::GetInstance().SaveFile(ProjectDocument::GetInstance().GetImagePieceFilePath());
	BitmapStyleDocument::GetInstance().SaveFile(ProjectDocument::GetInstance().GetBitmapStyleFilePath());
	NineGridStyleDocument::GetInstance().SaveFile(ProjectDocument::GetInstance().GetNineGridStyleFilePath());
	ColorStyleDocument::GetInstance().SaveFile(ProjectDocument::GetInstance().GetColorStyleFilePath());
	ClipBitmapStyleDocument::GetInstance().SaveFile(ProjectDocument::GetInstance().GetClipBitmapStyleFilePath());
	UpdateTitle(false);
}

void DesignerFrame::OnFileExit(wxCommandEvent& event)
{
	Close();
}

void DesignerFrame::OnClose(wxCloseEvent& event)
{
	if (IsModified())
	{
		wxMessageDialog dialog(this, wxT("Save Project ?"), wxT("Do you want to save the Project ?"), wxYES_NO|wxCANCEL);
		switch (dialog .ShowModal())
		{
		case wxID_YES:
			DoSaveFile();
			event.Skip();
			break;
		case wxID_NO:
			event.Skip();
			break;
		case wxID_CANCEL:
			break;
		}
	}
	else
	{
		event.Skip();
	}
}

bool DesignerFrame::IsModified() const
{
	if (ProjectDocument::GetInstance().isModified()) return true;
	if (ImagePieceDocument::GetInstance().isModified()) return true;
	if (BitmapStyleDocument::GetInstance().isModified()) return true;
	if (NineGridStyleDocument::GetInstance().isModified()) return true;
	if (ColorStyleDocument::GetInstance().isModified()) return true;
	if (ClipBitmapStyleDocument::GetInstance().isModified()) return true;

	return false;
}

void DesignerFrame::OnEditDelete(wxCommandEvent& event)
{
	switch (m_eCurrEditor)
	{
	case EDITOR_IMAGE_PIECE:
		{
			const PieceInfo* pPieceInfo = ImagePieceEditor::GetInstance().GetPiece();
			const ImageInfo* pImageInfo = ImagePieceEditor::GetInstance().GetImage();
			if (pPieceInfo) DoDeletePiece(pPieceInfo);
			else if (pImageInfo) DoDeleteImage(pImageInfo);
		}
		break;
	case EDITOR_BITMAP_STYLE:
		{
			const BitmapStyle* pBitmapStyle = BitmapStyleEditor::GetInstance().GetBitmapStyle();
			if (pBitmapStyle) DoDeleteBitmapStyle(pBitmapStyle);
		}
		break;
	case EDITOR_NINE_GRID_STYLE:
		{
			const NineGridStyle* pNineGridStyle = NineGridStyleEditor::GetInstance().GetNineGridStyle();
			if (pNineGridStyle) DoDeleteNineGridStyle(pNineGridStyle);
		}
		break;
	case EDITOR_COLOR_STYLE:
		{
			const ColorStyle* pColorStyle = ColorStyleEditor::GetInstance().GetColorStyle();
			if (pColorStyle) DoDeleteColorStyle(pColorStyle);
		}
		break;
	case EDITOR_CLIP_BITMAP_STYLE:
		{
			const ClipBitmapStyle* pClipBitmapStyle = ClipBitmapStyleEditor::GetInstance().GetClipBitmapStyle();
			if (pClipBitmapStyle) DoDeleteClipBitmapStyle(pClipBitmapStyle);
		}
		break;
	}
}

bool DesignerFrame::FindStyleIdsUsingThePiece(TS_WX_STRING& vBitmapStyleIds, TS_WX_STRING& vNineGridStyleIds, TS_WX_STRING& vClipBitmapStyleIds, const PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return false;

	BitmapStyleDocument::TV_BITMAP_STYLE vBitmapStyles;
	if (BitmapStyleDocument::GetInstance().EnumBitmapStyles(vBitmapStyles, pPieceInfo) > 0)
	{
		for (BitmapStyleDocument::TV_BITMAP_STYLE::iterator it = vBitmapStyles.begin(); it != vBitmapStyles.end(); ++it)
		{
			vBitmapStyleIds.insert((*it)->GetId());
		}
	}

	NineGridStyleDocument::TV_NINE_GRID_STYLE vNineGridStyles;
	if (NineGridStyleDocument::GetInstance().EnumNineGridStyles(vNineGridStyles, pPieceInfo) > 0)
	{
		for (NineGridStyleDocument::TV_NINE_GRID_STYLE::iterator it = vNineGridStyles.begin(); it != vNineGridStyles.end(); ++it)
		{
			vNineGridStyleIds.insert((*it)->GetId());
		}
	}

	ClipBitmapStyleDocument::TV_CLIP_BITMAP_STYLE vClipBitmapStyles;
	if (ClipBitmapStyleDocument::GetInstance().EnumClipBitmapStyles(vClipBitmapStyles, pPieceInfo) > 0)
	{
		for (ClipBitmapStyleDocument::TV_CLIP_BITMAP_STYLE::iterator it = vClipBitmapStyles.begin(); it != vClipBitmapStyles.end(); ++it)
		{
			vClipBitmapStyleIds.insert((*it)->GetId());
		}
	}

	return true;
}

bool DesignerFrame::MakeIdsString(wxString& strOut, const TS_WX_STRING& vIds, const wxString& strHeader)
{
	if (vIds.size() <= 0) return false;

	strOut += wxString::Format("\n\n%s\n", strHeader);
	for (TS_WX_STRING::const_iterator it = vIds.begin(); it != vIds.end(); ++it)
	{
		strOut += wxString::Format("\"%s\" ", (*it));
	}

	return true;
}

void DesignerFrame::DoDeletePiece(const PieceInfo* pPieceInfo)
{
	if (!pPieceInfo) return;

	// find styles using the piece
	TS_WX_STRING vBitmapStyleIds;
	TS_WX_STRING vNineGridStyleIds;
	TS_WX_STRING vClipBitmapStyleIds;
	FindStyleIdsUsingThePiece(vBitmapStyleIds, vNineGridStyleIds, vClipBitmapStyleIds, pPieceInfo);

	// make prompt string
	wxString strDeleteStyles;
	MakeIdsString(strDeleteStyles, vBitmapStyleIds, wxT("also delete bitmap styles:"));
	MakeIdsString(strDeleteStyles, vNineGridStyleIds, wxT("also delete 9-grid styles:"));
	MakeIdsString(strDeleteStyles, vClipBitmapStyleIds, wxT("also delete clip bitmap styles:"));

	// prompt
	wxString wxMsg = wxString::Format(wxT("Do you want to delete the piece: %s ?%s"), pPieceInfo->GetId(), strDeleteStyles);
	wxMessageDialog msgPrompt(this, wxMsg, wxT("Delete Piece"), wxYES_NO|wxCENTER);
	if (msgPrompt.ShowModal() != wxID_YES) return;

	// delete bitmap styles
	for (TS_WX_STRING::const_iterator it = vBitmapStyleIds.begin(); it != vBitmapStyleIds.end(); ++it)
	{
		BitmapStyleDocument::GetInstance().RemoveBitmapStyle((*it));
	}
	if (vBitmapStyleIds.size() > 0) BitmapStyleTransformer::GetInstance().UpdateListView();

	// delete nine grid styles
	for (TS_WX_STRING::const_iterator it = vNineGridStyleIds.begin(); it != vNineGridStyleIds.end(); ++it)
	{
		NineGridStyleDocument::GetInstance().RemoveNineGridStyle((*it));
	}
	if (vNineGridStyleIds.size() > 0) NineGridStyleTransformer::GetInstance().UpdateListView();

	// delete clip bitmap styles
	for (TS_WX_STRING::const_iterator it = vClipBitmapStyleIds.begin(); it != vClipBitmapStyleIds.end(); ++it)
	{
		ClipBitmapStyleDocument::GetInstance().RemoveClipBitmapStyle((*it));
	}
	if (vClipBitmapStyleIds.size() > 0) ClipBitmapStyleTransformer::GetInstance().UpdateListView();

	// delete the piece
	ImagePieceEditor::GetInstance().SetPiece(NULL);
	ImagePieceDocument::GetInstance().RemovePiece(pPieceInfo->GetId());
	PieceListTransformer::GetInstance().UpdateListView();
	PieceListTransformer::GetInstance().UpdateProperty(NULL);
}

void DesignerFrame::DoDeleteImage(const ImageInfo* pImageInfo)
{
	if (!pImageInfo) return;

	TS_WX_STRING vPieceInfoIds;
	TS_WX_STRING vBitmapStyleIds;
	TS_WX_STRING vNineGridStyleIds;
	TS_WX_STRING vClipBitmapStyleIds;

	// find pieces and styles using the image
	ImagePieceDocument::TV_PIECE_INFO vPieceInfo;
	if (ImagePieceDocument::GetInstance().EnumImagePieces(vPieceInfo, pImageInfo) > 0)
	{
		for (ImagePieceDocument::TV_PIECE_INFO::iterator it = vPieceInfo.begin(); it != vPieceInfo.end(); ++it)
		{
			const PieceInfo* pPieceInfo = (*it);
			vPieceInfoIds.insert(pPieceInfo->GetId());
			FindStyleIdsUsingThePiece(vBitmapStyleIds, vNineGridStyleIds, vClipBitmapStyleIds, pPieceInfo);
		}
	}

	// make prompt string
	wxString strDeletePiecesAndStyles;
	MakeIdsString(strDeletePiecesAndStyles, vBitmapStyleIds, wxT("also delete bitmap styles:"));
	MakeIdsString(strDeletePiecesAndStyles, vNineGridStyleIds, wxT("also delete 9-grid styles:"));
	MakeIdsString(strDeletePiecesAndStyles, vClipBitmapStyleIds, wxT("also delete clip bitmap styles:"));

	// prompt
	wxString wxMsg = wxString::Format(wxT("Do you want to delete the image: %s ?%s"), pImageInfo->GetId(), strDeletePiecesAndStyles);
	wxMessageDialog msgPrompt(this, wxMsg, wxT("Delete Image"), wxYES_NO|wxCENTER);
	if (msgPrompt.ShowModal() != wxID_YES) return;

	// delete bitmap styles
	for (TS_WX_STRING::const_iterator it = vBitmapStyleIds.begin(); it != vBitmapStyleIds.end(); ++it)
	{
		BitmapStyleDocument::GetInstance().RemoveBitmapStyle((*it));
	}
	if (vBitmapStyleIds.size() > 0) BitmapStyleTransformer::GetInstance().UpdateListView();

	// delete nine grid styles
	for (TS_WX_STRING::const_iterator it = vNineGridStyleIds.begin(); it != vNineGridStyleIds.end(); ++it)
	{
		NineGridStyleDocument::GetInstance().RemoveNineGridStyle((*it));
	}
	if (vNineGridStyleIds.size() > 0) NineGridStyleTransformer::GetInstance().UpdateListView();

	// delete clip bitmap styles
	for (TS_WX_STRING::const_iterator it = vClipBitmapStyleIds.begin(); it != vClipBitmapStyleIds.end(); ++it)
	{
		ClipBitmapStyleDocument::GetInstance().RemoveClipBitmapStyle((*it));
	}
	if (vClipBitmapStyleIds.size() > 0) ClipBitmapStyleTransformer::GetInstance().UpdateListView();

	// delete the pieces
	for (TS_WX_STRING::const_iterator it = vPieceInfoIds.begin(); it != vPieceInfoIds.end(); ++it)
	{
		ImagePieceDocument::GetInstance().RemovePiece((*it));
	}
	if (vPieceInfoIds.size() > 0) PieceListTransformer::GetInstance().UpdateListView();

	// delete the image
	ImagePieceEditor::GetInstance().SetImage(NULL);
	ImagePieceDocument::GetInstance().RemoveImage(pImageInfo->GetId());
	ImageListTransformer::GetInstance().UpdateListView();
	ImageListTransformer::GetInstance().UpdateProperty(NULL);
}

void DesignerFrame::DoDeleteBitmapStyle(const BitmapStyle* pBitmapStyle)
{
	if (!pBitmapStyle) return;
	wxString wxMsg = wxString::Format(wxT("Do you want to delete the bitmap style: %s"), pBitmapStyle->GetId());
	wxMessageDialog msgPrompt(this, wxMsg, wxT("Delete Bitmap Style"), wxYES_NO|wxCENTER);
	if (msgPrompt.ShowModal() == wxID_YES)
	{
		// delete bitmap style
		BitmapStyleEditor::GetInstance().SetBitmapStyle(NULL);
		BitmapStyleDocument::GetInstance().RemoveBitmapStyle(pBitmapStyle->GetId());
		BitmapStyleTransformer::GetInstance().UpdateListView();
		BitmapStyleTransformer::GetInstance().UpdateProperty(NULL);
	}
}

void DesignerFrame::DoDeleteNineGridStyle(const NineGridStyle* pNineGridStyle)
{
	if (!pNineGridStyle) return;
	wxString wxMsg = wxString::Format(wxT("Do you want to delete the 9-grid style: %s"), pNineGridStyle->GetId());
	wxMessageDialog msgPrompt(this, wxMsg, wxT("Delete 9-Grid Style"), wxYES_NO|wxCENTER);
	if (msgPrompt.ShowModal() == wxID_YES)
	{
		// delete nine grid style
		NineGridStyleEditor::GetInstance().SetNineGridStyle(NULL);
		NineGridStyleDocument::GetInstance().RemoveNineGridStyle(pNineGridStyle->GetId());
		NineGridStyleTransformer::GetInstance().UpdateListView();
		NineGridStyleTransformer::GetInstance().UpdateProperty(NULL);
	}
}

void DesignerFrame::DoDeleteColorStyle(const ColorStyle* pColorStyle)
{
	if (!pColorStyle) return;
	wxString wxMsg = wxString::Format(wxT("Do you want to delete the color style: %s"), pColorStyle->GetId());
	wxMessageDialog msgPrompt(this, wxMsg, wxT("Delete Color Style"), wxYES_NO|wxCENTER);
	if (msgPrompt.ShowModal() == wxID_YES)
	{
		// delete color style
		ColorStyleEditor::GetInstance().SetColorStyle(NULL);
		ColorStyleDocument::GetInstance().RemoveColorStyle(pColorStyle->GetId());
		ColorStyleTransformer::GetInstance().UpdateListView();
		ColorStyleTransformer::GetInstance().UpdateProperty(NULL);
	}
}

void DesignerFrame::DoDeleteClipBitmapStyle(const ClipBitmapStyle* pClipBitmapStyle)
{
	if (!pClipBitmapStyle) return;
	wxString wxMsg = wxString::Format(wxT("Do you want to delete the clip bitmap style: %s"), pClipBitmapStyle->GetId());
	wxMessageDialog msgPrompt(this, wxMsg, wxT("Delete Clip Bitmap Style"), wxYES_NO|wxCENTER);
	if (msgPrompt.ShowModal() == wxID_YES)
	{
		// delete clip bitmap style
		ClipBitmapStyleEditor::GetInstance().SetClipBitmapStyle(NULL);
		ClipBitmapStyleDocument::GetInstance().RemoveClipBitmapStyle(pClipBitmapStyle->GetId());
		ClipBitmapStyleTransformer::GetInstance().UpdateListView();
		ClipBitmapStyleTransformer::GetInstance().UpdateProperty(NULL);
	}
}

void DesignerFrame::OnAddPiece(wxCommandEvent& event)
{
	DialogAddPiece dialog(this);
	dialog.ShowModal();
	const ImageInfo* pImageInfo = dialog.GetCurrImageInfo();
	if (pImageInfo)
	{
		m_pListNotebook->SetSelection(LIST_VIEW_IMAGE);
		SwitchEditor(EDITOR_IMAGE_PIECE);
		ImagePieceEditor::GetInstance().SetImage(pImageInfo);
	}
}

void DesignerFrame::OnAddBitmapStyle(wxCommandEvent& event)
{
	const BitmapStyle* pNewBitmapStyle = BitmapStyleDocument::GetInstance().AddBitmapStyle("bs_bitmap_style");
	BitmapStyleTransformer::GetInstance().UpdateListView();
	BitmapStyleTransformer::GetInstance().SetSelectedBitmapStyle(pNewBitmapStyle);
	m_pListNotebook->SetSelection(LIST_VIEW_BITMAP_STYLE);
}

void DesignerFrame::OnAddNineGridStyle(wxCommandEvent& event)
{
	const NineGridStyle* pNewNineGridStyle = NineGridStyleDocument::GetInstance().AddNineGridStyle("ngs_nine_grid_style");
	NineGridStyleTransformer::GetInstance().UpdateListView();
	NineGridStyleTransformer::GetInstance().SetSelectedNineGridStyle(pNewNineGridStyle);
	m_pListNotebook->SetSelection(LIST_VIEW_NINE_GRID_STYLE);
}

void DesignerFrame::OnAddColorStyle(wxCommandEvent& event)
{
	const ColorStyle* pNewColorStyle = ColorStyleDocument::GetInstance().AddColorStyle("cs_color_style");
	ColorStyleTransformer::GetInstance().UpdateListView();
	ColorStyleTransformer::GetInstance().SetSelectedColorStyle(pNewColorStyle);
	m_pListNotebook->SetSelection(LIST_VIEW_COLOR_STYLE);
}

void DesignerFrame::OnAddClipBitmapStyle(wxCommandEvent& event)
{
	const ClipBitmapStyle* pNewClipBitmapStyle = ClipBitmapStyleDocument::GetInstance().AddClipBitmapStyle("cbs_clip_bitmap_style");
	ClipBitmapStyleTransformer::GetInstance().UpdateListView();
	ClipBitmapStyleTransformer::GetInstance().SetSelectedClipBitmapStyle(pNewClipBitmapStyle);
	m_pListNotebook->SetSelection(LIST_VIEW_CLIP_BITMAP_STYLE);
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
	SwitchEditor(EDITOR_IMAGE_PIECE);
	const PieceInfo* pPieceInfo = PieceListTransformer::GetInstance().GetSelectedPieceInfo();
	if (pPieceInfo)
	{
		const ImageInfo* pImageInfo = pPieceInfo->GetImageInfo();
		ImagePieceEditor::GetInstance().SetImage(pImageInfo);
		ImageListTransformer::GetInstance().SetSelectedImageInfo(pImageInfo);
	}
	ImagePieceEditor::GetInstance().SetPiece(pPieceInfo);
	PieceListTransformer::GetInstance().UpdateProperty(pPieceInfo);
}

void DesignerFrame::OnImageListSelected(wxTreeEvent& event)
{
	SwitchEditor(EDITOR_IMAGE_PIECE);
	const ImageInfo* pImageInfo = ImageListTransformer::GetInstance().GetSelectedImageInfo();
	ImagePieceEditor::GetInstance().SetImage(pImageInfo);
	ImagePieceEditor::GetInstance().SetPiece(NULL);
	ImageListTransformer::GetInstance().UpdateProperty(pImageInfo);
}

void DesignerFrame::OnBitmapStyleListSelected(wxTreeEvent& event)
{
	SwitchEditor(EDITOR_BITMAP_STYLE);
	const BitmapStyle* pBitmapStyle = BitmapStyleTransformer::GetInstance().GetSelectedBitmapStyle();
	BitmapStyleEditor::GetInstance().SetBitmapStyle(pBitmapStyle);
	BitmapStyleTransformer::GetInstance().UpdateProperty(pBitmapStyle);
}

void DesignerFrame::OnNineGridStyleListSelected(wxTreeEvent& event)
{
	SwitchEditor(EDITOR_NINE_GRID_STYLE);
	const NineGridStyle* pNineGridStyle = NineGridStyleTransformer::GetInstance().GetSelectedNineGridStyle();
	NineGridStyleEditor::GetInstance().SetNineGridStyle(pNineGridStyle);
	NineGridStyleTransformer::GetInstance().UpdateProperty(pNineGridStyle);
}

void DesignerFrame::OnColorStyleListSelected(wxTreeEvent& event)
{
	SwitchEditor(EDITOR_COLOR_STYLE);
	const ColorStyle* pColorStyle = ColorStyleTransformer::GetInstance().GetSelectedColorStyle();
	ColorStyleEditor::GetInstance().SetColorStyle(pColorStyle);
	ColorStyleTransformer::GetInstance().UpdateProperty(pColorStyle);
}

void DesignerFrame::OnClipBitmapStyleListSelected(wxTreeEvent& event)
{
	SwitchEditor(EDITOR_CLIP_BITMAP_STYLE);
	const ClipBitmapStyle* pClipBitmapStyle = ClipBitmapStyleTransformer::GetInstance().GetSelectedClipBitmapStyle();
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

void DesignerFrame::SwitchEditor(EDITOR eEditor)
{
	for (int i = 0; i < NUM_EDITOR; ++i)
	{
		if (i == eEditor)
		{
			m_pEditorNotebook->SetSelection(eEditor);
			m_eCurrEditor = eEditor;
		}
		else
		{
			m_pEditors[i]->Reset();
		}
	}
}
