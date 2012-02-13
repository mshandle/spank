/*!
 * \file UIDesignerFrame.cpp
 * \date 8-31-2011 13:20:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UIDesignerFrame.h"
#include <wx/menu.h>
#include <wx/propgrid/propgrid.h>
#include <wx/propgrid/advprops.h>
#include <wx/filedlg.h>

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

BEGIN_EVENT_TABLE(UIDesignerFrame, wxFrame)
	EVT_MENU(wxID_OPEN, UIDesignerFrame::OnFileOpen)
	EVT_MENU(wxID_SAVE, UIDesignerFrame::OnFileSave)
	EVT_MENU(wxID_CLOSE, UIDesignerFrame::OnFileClose)
	EVT_MENU(wxID_EXIT, UIDesignerFrame::OnExit)

	EVT_MENU(wxID_ZOOM_100, UIDesignerFrame::OnViewZoom100)
	EVT_MENU(wxID_ZOOM_IN, UIDesignerFrame::OnViewZoomIn)
	EVT_MENU(wxID_ZOOM_OUT, UIDesignerFrame::OnViewZoomOut)

	EVT_TREE_SEL_CHANGED(IDC_IMAGE_PIECE_LIST, UIDesignerFrame::OnImagePieceListSelected)
	EVT_TREE_SEL_CHANGED(IDC_IMAGE_LIST, UIDesignerFrame::OnImageListSelected)
END_EVENT_TABLE()

IMPLEMENT_DYNAMIC_CLASS(UIDesignerFrame, wxFrame)

UIDesignerFrame::UIDesignerFrame()
:wxFrame(NULL, wxID_ANY, wxT("UI Designer"), wxDefaultPosition, wxSize(800, 600))
{
	CreateControls();
}

UIDesignerFrame::~UIDesignerFrame()
{
	m_auiManager.UnInit();
	SAFE_DELETE(m_pImagePieceDocument);
}

void UIDesignerFrame::Init()
{
	m_pNotebookView = NULL;
	m_pImagePieceListView = NULL;
	m_pImageListView = NULL;

	m_pImagePieceEditor = NULL;
	m_pImagePieceDocument = NULL;
}

void UIDesignerFrame::CreateControls()
{
	m_auiManager.SetManagedWindow(this);

	CreateMenu();
	CreateToolbar();
	CreateProjectView();
	CreatePropertyView();
	CreateEditorView();
	CreateOutputView();

	m_pImagePieceDocument = new UIImagePieceDocument();

	m_auiManager.Update();
}

void UIDesignerFrame::CreateMenu()
{
	wxMenuBar* pMenuBar = new wxMenuBar();

	// file
	wxMenu* pMenuItemFile = new wxMenu();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, wxID_OPEN, wxT("&Open...\tCtrl+O"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/folder-horizontal-open.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemFile->Append(menuItem);
	}
	pMenuItemFile->AppendSeparator();
	pMenuItemFile->Append(wxID_CLOSE, wxT("&Close"), wxEmptyString, wxITEM_NORMAL);

	pMenuItemFile->AppendSeparator();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, wxID_SAVE, wxT("&Save\tCtrl+S"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/disk.png"), wxBITMAP_TYPE_PNG);
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
		wxBitmap bitmap(wxT("images/zoom.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, wxID_ZOOM_IN, wxT("Zoom &In\tCtrl++"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/zoom_in.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemView->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemView, wxID_ZOOM_OUT, wxT("Zoom &Out\tCtrl+-"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/zoom_out.png"), wxBITMAP_TYPE_PNG);
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

void UIDesignerFrame::CreateToolbar()
{
	wxAuiToolBar* pAuiToolBar = new wxAuiToolBar(this, IDC_TOOLBAR, wxDefaultPosition, wxDefaultSize, 0);

	{
		wxBitmap bitmap(wxT("images/document--plus.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_NEW, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/folder-horizontal-open.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_OPEN, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/disk.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_SAVE, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	pAuiToolBar->AddSeparator();

	{
		wxBitmap bitmap(wxT("images/zoom.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_ZOOM_100, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/zoom_in.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(wxID_ZOOM_IN, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/zoom_out.png"), wxBITMAP_TYPE_PNG);
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

void UIDesignerFrame::CreateProjectView()
{
	m_pNotebookView = new wxNotebook(this, IDC_NOTEBOOK, wxDefaultPosition, wxSize(400, 500), wxNO_BORDER);
	m_auiManager.AddPane(m_pNotebookView, wxAuiPaneInfo()
		.Name(wxT("Project"))
		.Caption(wxT("Project"))
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

	m_pImagePieceListView = new wxTreeCtrl(m_pNotebookView, IDC_IMAGE_PIECE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pNotebookView->AddPage(m_pImagePieceListView, "Image Piece List");

	m_pImageListView = new wxTreeCtrl(m_pNotebookView, IDC_IMAGE_LIST, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
	m_pNotebookView->AddPage(m_pImageListView, "Image List");
}

void UIDesignerFrame::CreatePropertyView()
{
	m_pPropertyGrid = new wxPropertyGrid(this, IDC_PROPERTY, wxDefaultPosition, wxSize(300, 100), wxPG_SPLITTER_AUTO_CENTER|wxNO_BORDER);
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

void UIDesignerFrame::CreateEditorView()
{
	m_pImagePieceEditor = new UIImagePieceEditor(this, IDC_EDITOR_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	m_auiManager.AddPane(m_pImagePieceEditor, wxAuiPaneInfo()
		.Name(wxT("Editor"))
		.Caption(wxT("Editor"))
		.Centre()
		.CaptionVisible(false)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.Movable(false));
	
}

void UIDesignerFrame::CreateOutputView()
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

void UIDesignerFrame::UpdateImagePieceView()
{
	m_pImagePieceListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pImagePieceListView->AddRoot(wxT("ImagePiece"));

	const UIImagePieceDocument::TM_PIECE_INFO& pieceInfoMap = m_pImagePieceDocument->GetPieceInfoMap();
	for (UIImagePieceDocument::TM_PIECE_INFO::const_iterator it = pieceInfoMap.begin(); it != pieceInfoMap.end(); ++it)
	{
		const PieceInfo* pPieceInfo = it->second;
		m_pImagePieceListView->AppendItem(rootItem, pPieceInfo->GetId());
	}
	m_pImagePieceListView->ExpandAll();

	wxTreeItemIdValue value;
	if(pieceInfoMap.empty()) return;
	m_pImagePieceListView->SelectItem(m_pImagePieceListView->GetFirstChild(rootItem, value));
}

void UIDesignerFrame::UpdateImageListView()
{
	m_pImageListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pImageListView->AddRoot(wxT("ImageInfo"));

	const UIImagePieceDocument::TM_IMAGE_INFO& ImageInfoMap = m_pImagePieceDocument->GetImageInfoMap();
	for (UIImagePieceDocument::TM_IMAGE_INFO::const_iterator it = ImageInfoMap.begin(); it != ImageInfoMap.end(); ++it)
	{
		const ImageInfo* pImageInfo = it->second;
		m_pImageListView->AppendItem(rootItem, pImageInfo->GetId());
	}
	m_pImageListView->ExpandAll();

	wxTreeItemIdValue value;
	if(ImageInfoMap.empty()) return;
	m_pImageListView->SelectItem(m_pImageListView->GetFirstChild(rootItem, value));

}

void UIDesignerFrame::UpdateImagePieceEditor(const PieceInfo* pPieceInfo)
{
// 	if (pPieceInfo)
// 	{
// 		const wxString& strImage = m_pImagePieceDocument->FindImage(pPieceInfo->nImageId);
// 		m_pImagePieceEditor->LoadImageFromFile(strImage);
// 	}
// 	m_pImagePieceEditor->SetSelectedPiece(pPieceInfo);
}

void UIDesignerFrame::OnFileOpen(wxCommandEvent& event)
{
	wxFileDialog dialog(this, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("XML files (*.xml)|*.xml"), wxFD_DEFAULT_STYLE);
	if (dialog .ShowModal() == wxID_OK)
	{
		wxString strPath = dialog.GetPath();
		m_pImagePieceDocument->OpenFile(strPath);
		UpdateImagePieceView();
		UpdateImageListView();
	}
}

void UIDesignerFrame::OnFileSave(wxCommandEvent& event)
{
	if (m_pImagePieceDocument && !m_pImagePieceDocument->GetFileName().IsEmpty())
	{
		m_pImagePieceDocument->SaveFile(m_pImagePieceDocument->GetFileName());
	}
}

void UIDesignerFrame::OnFileClose(wxCommandEvent& event)
{
	wxMessageDialog Dialog(NULL,"Don't you want to close the file",wxEmptyString, wxNO_DEFAULT|wxYES_NO);
	if (Dialog.ShowModal() != wxID_YES) return;

	const UIImagePieceDocument::TM_IMAGE_INFO& ImageInfoMap = m_pImagePieceDocument->GetImageInfoMap();
	if (ImageInfoMap.size() > 0)
	{
		wxMessageDialog MessageDialog(NULL, "Do you want to save the file", wxEmptyString, wxNO_DEFAULT|wxYES_NO);
		if (MessageDialog.ShowModal() == wxID_YES) m_pImagePieceDocument->SaveFile(m_pImagePieceDocument->GetFileName());		
		m_pImagePieceDocument->Clear();
		UpdateImagePieceView();
		UpdateImageListView();
	}
}

void UIDesignerFrame::OnExit(wxCommandEvent& event)
{
	Destroy();
}

void UIDesignerFrame::OnViewZoom100(wxCommandEvent& event)
{
	m_pImagePieceEditor->Zoom(UIImagePieceEditor::ZOOM_MIN);
}

void UIDesignerFrame::OnViewZoomIn(wxCommandEvent& event)
{
	m_pImagePieceEditor->ZoomIn();
}

void UIDesignerFrame::OnViewZoomOut(wxCommandEvent& event)
{
	m_pImagePieceEditor->ZoomOut();
}

void UIDesignerFrame::OnImagePieceListSelected(wxTreeEvent& event)
{
	wxString strPieceId = m_pImagePieceListView->GetItemText(m_pImagePieceListView->GetSelection());
	PieceInfo* pPieceInfo = m_pImagePieceDocument->FindPieceInfo(strPieceId);
	if (pPieceInfo)
	{
		ImageInfo* pImageInfo = m_pImagePieceDocument->FindImageInfo(pPieceInfo->GetImageId());
		m_pImagePieceEditor->SetImage(pImageInfo);
	}
	m_pImagePieceEditor->SetSelection(pPieceInfo);
}

void UIDesignerFrame::OnImageListSelected(wxTreeEvent& event)
{
	wxString strImageId = m_pImageListView->GetItemText(m_pImageListView->GetSelection());
	ImageInfo* pImageInfo = m_pImagePieceDocument->FindImageInfo(strImageId);
	m_pImagePieceEditor->SetImage(pImageInfo);
	m_pImagePieceEditor->SetSelection(NULL);
}
