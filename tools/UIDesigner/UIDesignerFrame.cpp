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
#include "UIAddPieceInfoView.h"
#include "UIAddImageInfoView.h"
#include "UINewImagePieceView.h"
#include "UITipsDialogView.h"
#include "UIImportPieceView.h"
#include "CombinaPiece.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

BEGIN_EVENT_TABLE(UIDesignerFrame, wxFrame)
	EVT_MENU(wxID_NEW, UIDesignerFrame::OnFileNew)
	EVT_MENU(wxID_OPEN, UIDesignerFrame::OnFileOpen)
	EVT_MENU(wxID_SAVE, UIDesignerFrame::OnFileSave)
	EVT_MENU(wxID_CLOSE, UIDesignerFrame::OnFileClose)
	EVT_MENU(wxID_EXIT, UIDesignerFrame::OnExit)
	EVT_MENU(ID_LAYOUT_MOVE_LEFT, UIDesignerFrame::OnLayoutMoveLeft)
	EVT_MENU(ID_LAYOUT_MOVE_RIGHT, UIDesignerFrame::OnLayoutMoveRight)
	EVT_MENU(ID_LAYOUT_MOVE_UP, UIDesignerFrame::OnLayoutMoveUp)
	EVT_MENU(ID_LAYOUT_MOVE_DOWN, UIDesignerFrame::OnLayoutMoveDown)

	EVT_MENU(wxID_ZOOM_100, UIDesignerFrame::OnViewZoom100)
	EVT_MENU(wxID_ZOOM_IN, UIDesignerFrame::OnViewZoomIn)
	EVT_MENU(wxID_ZOOM_OUT, UIDesignerFrame::OnViewZoomOut)

	EVT_MENU(ID_ADDPIECEMENU, UIDesignerFrame::OnAddPieceInfo)
	EVT_MENU(ID_DELETE_PIECE, UIDesignerFrame::OnDeletePieceInfo)
	EVT_MENU(ID_ADDIMAGEMENU, UIDesignerFrame::OnAddImageInfo)
	EVT_MENU(ID_DELETE_IMAGE, UIDesignerFrame::OnDeleteImageInfo)
	EVT_MENU(ID_CUT_PIECE, UIDesignerFrame::OnCutPiece)
	EVT_MENU(IDC_IMPORT_PIECE, UIDesignerFrame::OnImport)
	EVT_PG_CHANGED(IDC_PROPERTYPIECE, UIDesignerFrame::OnPiecePropertyGridChange)
	EVT_PG_CHANGED(IDC_IMPORT_PROPERTY, UIDesignerFrame::OnImportPropertyGridChange)
	EVT_TREE_SEL_CHANGED(IDC_PROJECT, UIDesignerFrame::OnProjectPieceItemSelChanged)
	EVT_TREE_ITEM_MENU(IDC_PROJECT, UIDesignerFrame::OnProjectPieceRightClick)
	EVT_TREE_SEL_CHANGED(IDC_PROJECTIMAGE, UIDesignerFrame::OnProjectImageItemSelChanged)
	EVT_TREE_ITEM_MENU(IDC_PROJECTIMAGE, UIDesignerFrame::OnProjectImageViewRightClick)

	EVT_TREE_SEL_CHANGED(IDC_IMAPORT_PIECE_VIEW, UIDesignerFrame::OnProjectImportItemSleChanged)
	EVT_TREE_ITEM_MENU(IDC_IMAPORT_PIECE_VIEW, UIDesignerFrame::OnProjectImportRightClick)
	EVT_IMAGE_PIECE_CHANGED(IDC_INPUT_VIEW, UIDesignerFrame::OnImagePieceChanged)
	EVT_MENU(IDC_DELETE_IMPORTPIECE, UIDesignerFrame::OnDelteImportPiece)
	EVT_MENU(IDC_LOAD_IMPORTPIECE, UIDesignerFrame::OnLoadImportPiece)
	EVT_MENU(IDC_SORT_PIECE, UIDesignerFrame::OnSortPiece)
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
	m_pProjectViewPiece = NULL;
	m_pImagePieceView = NULL;
	m_pImagePieceDocument = NULL;
}

void UIDesignerFrame::CreateControls()
{
	m_auiManager.SetManagedWindow(this);

	CreateMenu();
	CreateToolbar();
	CreateProjectView();
	CreatePropertyView();
	CreateInputView();
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
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemFile, wxID_NEW, wxT("&New...\tCtrl+N"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/document--plus.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemFile->Append(menuItem);
	}
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

	pMenuItemFile->AppendSeparator();
	pMenuItemFile->Append(IDC_IMPORT_PIECE, wxT("&Impot\tCtrl+A"), wxEmptyString, wxITEM_NORMAL);

	pMenuItemFile->Append(wxID_SAVEAS, wxT("Save &As...\tCtrl+Shift+S"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemFile->AppendSeparator();
	pMenuItemFile->Append(wxID_EXIT, wxT("E&xit\tAlt+F4"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemFile, wxT("&File"));


	// edit
	wxMenu* pMenuItemEdit = new wxMenu();
	pMenuItemEdit->Append(ID_EDIT_UNDO, wxT("&Undo\tCtrl+Z"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_REDO, wxT("&Redo\tCtrl+Y"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->AppendSeparator();
	pMenuItemEdit->Append(ID_EDIT_COPY, wxT("&Copy\tCtrl+C"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_CUT, wxT("Cu&t\tCtrl+X"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_PAST, wxT("&Past\tCtrl+V"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(ID_EDIT_DELETE, wxT("&Delete\tDel"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemEdit->Append(IDC_SORT_PIECE, wxT("&Sort Piece"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemEdit, wxT("&Edit"));

	// layer
	wxMenu* pMenuItemLayer = new wxMenu();
	wxMenu* pMenuItemLayerAlign = new wxMenu();
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_LEFT, wxT("Align &Left"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_left.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_RIGHT, wxT("Align &Right"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_right.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_TOP, wxT("Align &Top"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_top.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_BOTTOM, wxT("Align &Bottom"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_bottom.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_CENTER, wxT("Align &Center"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_center.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	{
		wxMenuItem* menuItem = new wxMenuItem(pMenuItemLayerAlign, ID_LAYOUT_ALIGN_MIDDLE, wxT("Align &Middle"), wxEmptyString, wxITEM_NORMAL);
		wxBitmap bitmap(wxT("images/shape_aling_middle.png"), wxBITMAP_TYPE_PNG);
		menuItem->SetBitmap(bitmap);
		pMenuItemLayerAlign->Append(menuItem);
	}
	pMenuItemLayer->Append(ID_LAYOUT_ALIGN, wxT("&Align"), pMenuItemLayerAlign);
	wxMenu* pMenuItemLayerMove = new wxMenu();
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_LEFT, wxT("Move &Left\tLeft"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_RIGHT, wxT("Move &Right\tRight"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_UP, wxT("Move &Up\tUp"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayerMove->Append(ID_LAYOUT_MOVE_DOWN, wxT("Move &Down\tDown"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemLayer->Append(ID_LAYOUT_MOVE, wxT("&Move"), pMenuItemLayerMove);
	pMenuBar->Append(pMenuItemLayer, wxT("&Layout"));

	// view
	wxMenu* pMenuItemView = new wxMenu();
	pMenuItemView->Append(ID_VIEW_GRID, wxT("Show &Grid\tCtrl+G"), wxEmptyString, wxITEM_CHECK);
	pMenuItemView->Check(ID_VIEW_GRID, true);
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
	pMenuItemTool->Append(ID_TOOL_PREFERENCES, wxT("&Preferences..."), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemTool, wxT("&Tools"));

	// help
	wxMenu* pMenuItemHelp = new wxMenu();
	pMenuItemHelp->Append(ID_HELP_SUPPORT, wxT("&Support"), wxEmptyString, wxITEM_NORMAL);
	pMenuItemHelp->AppendSeparator();
	pMenuItemHelp->Append(ID_HELP_ABOUT, wxT("&About\tF1"), wxEmptyString, wxITEM_NORMAL);
	pMenuBar->Append(pMenuItemHelp, wxT("&Help"));

	SetMenuBar(pMenuBar);
}

void UIDesignerFrame::CreateToolbar()
{
	wxAuiToolBar* pAuiToolBar = new wxAuiToolBar(this, ID_TOOLBAR, wxDefaultPosition, wxDefaultSize, 0);

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
		wxBitmap bitmap(wxT("images/shape_aling_left.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_LEFT, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_right.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_RIGHT, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_top.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_TOP, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_bottom.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_BOTTOM, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_center.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_CENTER, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
	}

	{
		wxBitmap bitmap(wxT("images/shape_aling_middle.png"), wxBITMAP_TYPE_PNG);
		wxBitmap bitmapDisabled;
		pAuiToolBar->AddTool(ID_LAYOUT_ALIGN_MIDDLE, wxEmptyString, bitmap, bitmapDisabled, wxITEM_NORMAL, wxEmptyString, wxEmptyString, NULL);
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
	//m_pProjectView = new wxTreeCtrl(this, IDC_PROJECT, wxDefaultPosition, wxDefaultSize, wxTR_SINGLE|wxNO_BORDER);
	m_pProjectViewPiece = new wxTreeCtrl( this, IDC_PROJECT, wxDefaultPosition, wxSize(200, 100), wxTR_SINGLE );
	m_auiManager.AddPane(m_pProjectViewPiece, wxAuiPaneInfo()
		.Name(_T("PieceView")).CaptionVisible(true).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));

	m_pProjectViewImage = new wxTreeCtrl( this, IDC_PROJECTIMAGE, wxDefaultPosition, wxSize(200, 100), wxTR_SINGLE );
	m_auiManager.AddPane(m_pProjectViewImage, wxAuiPaneInfo()
		.Name(_T("ImageView")).CaptionVisible(true).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));

	m_pImportPieceView = new wxTreeCtrl(this,IDC_IMAPORT_PIECE_VIEW, wxDefaultPosition, wxSize(300, 300),wxTR_SINGLE);
	m_auiManager.AddPane(m_pImportPieceView, wxAuiPaneInfo()
		.Name(_T("ImportPiece")).CaptionVisible(true).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));

}

void UIDesignerFrame::CreatePropertyView()
{
	m_pPieceProperty = new wxPropertyGrid(this, IDC_PROPERTYPIECE, wxDefaultPosition, wxSize(300, 100), wxPG_SPLITTER_AUTO_CENTER|wxNO_BORDER);
	m_pProtertyStrID = new wxStringProperty("StrID", wxPG_LABEL);
	m_pPieceProperty->Append(m_pProtertyStrID);
	m_pProtertyX = new wxIntProperty("X", wxPG_LABEL);
	m_pPieceProperty->Append(m_pProtertyX);
	m_pProtertyY = new wxIntProperty("Y", wxPG_LABEL);
	m_pPieceProperty->Append(m_pProtertyY);
	m_pProtertyWidth = new wxIntProperty("Width", wxPG_LABEL);
	m_pPieceProperty->Append(m_pProtertyWidth);
	m_pProtertyHight = new wxIntProperty("Hight ", wxPG_LABEL);
	m_pPieceProperty->Append(m_pProtertyHight);
	

	m_pImageProperty = new wxPropertyGrid(this, IDC_PROPERTYIMAGE, wxDefaultPosition, wxSize(300, 300), wxPG_SPLITTER_AUTO_CENTER|wxNO_BORDER);
	m_pImageFileNameProterty = new wxStringProperty("ImageFileName", wxPG_LABEL);
	m_pImageProperty->Append(m_pImageFileNameProterty);
	m_pImageIDProterty = new wxIntProperty("ImageID",wxPG_LABEL);
	m_pImageProperty->Append(m_pImageIDProterty);

	m_pImportPieceProperty = new wxPropertyGrid(this, IDC_IMPORT_PROPERTY, wxDefaultPosition, wxSize(300, 300), wxPG_SPLITTER_AUTO_CENTER|wxNO_BORDER);
	m_pImportPieceFileName = new wxStringProperty("FileName", wxPG_LABEL);
	m_pImportPieceProperty->Append(m_pImportPieceFileName);
	m_pImageID = new wxIntProperty("ImageID", wxPG_LABEL);
	m_pImportPieceProperty->Append(m_pImageID);
	m_pImportPieceX = new wxIntProperty("X", wxPG_LABEL);
	m_pImportPieceProperty->Append(m_pImportPieceX);
	m_pImportPieceY = new wxIntProperty("Y", wxPG_LABEL);
	m_pImportPieceProperty->Append(m_pImportPieceY);

	m_auiManager.AddPane(m_pPieceProperty, wxAuiPaneInfo()
		.Name(wxT("PieceProerty"))
		.Caption(wxT("Piece"))
		.Right()
		.BestSize(wxSize(300, 300))
		.Position(1)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(300, 500))
		.Movable(false));

	m_auiManager.AddPane(m_pImageProperty, wxAuiPaneInfo()
		.Name(wxT("ImageProerty"))
		.Caption(wxT("Image"))
		.Right()
		.BestSize(wxSize(300, 300))
		.Position(1)
		.CloseButton(false)
		.DestroyOnClose(false)
		.Resizable(true)
		.Floatable(false)
		.FloatingSize(wxSize(300, 500))
		.Movable(false));

	m_auiManager.AddPane(m_pImportPieceProperty, wxAuiPaneInfo()
		.Name(wxT("ImportPieceProterty"))
		.Caption(wxT("ImportPiece"))
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

void UIDesignerFrame::CreateInputView()
{
	m_pImagePieceView = new UIImagePieceView(this, IDC_INPUT_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER|wxFRAME_NO_TASKBAR);
	m_auiManager.AddPane(m_pImagePieceView, wxAuiPaneInfo()
		.Name(wxT("Input"))
		.Caption(wxT("Input"))
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

void UIDesignerFrame::UpdateProjectView()
{
	m_pProjectViewPiece->DeleteAllItems();
	wxTreeItemId rootItem = m_pProjectViewPiece->AddRoot(wxT("ImagePiece"));

	const UIImagePieceDocument::TM_PIECE_INFO& pieceInfoMap = m_pImagePieceDocument->GetPieceInfoMap();
	for (UIImagePieceDocument::TM_PIECE_INFO::const_iterator it = pieceInfoMap.begin(); it != pieceInfoMap.end(); ++it)
	{
		const UIImagePieceDocument::PIECE_INFO& pieceInfo = it->second;
		m_pProjectViewPiece->AppendItem(rootItem, pieceInfo.strID);
	}
	m_pProjectViewPiece->ExpandAll();

	wxTreeItemIdValue value;
	if(pieceInfoMap.empty()) return;
	m_pProjectViewPiece->SelectItem(m_pProjectViewPiece->GetFirstChild(rootItem, value));
}

void UIDesignerFrame::UpDateProjectImageView()
{
	m_pProjectViewImage->DeleteAllItems();
	wxTreeItemId rootItem = m_pProjectViewImage->AddRoot(wxT("ImageInfo"));

	const UIImagePieceDocument::TM_IMAGE_INFO& ImageMap = m_pImagePieceDocument->GetImageMap();
	for (UIImagePieceDocument::TM_IMAGE_INFO::const_iterator it = ImageMap.begin(); it != ImageMap.end(); ++it)
	{
		const UIImagePieceDocument::IMAGE_INFO& pieceInfo = it->second;
		m_pProjectViewImage->AppendItem(rootItem, pieceInfo.strFile);
	}
	m_pProjectViewImage->ExpandAll();

	wxTreeItemIdValue value;
	if(ImageMap.empty()) return;
	m_pProjectViewImage->SelectItem(m_pProjectViewImage->GetFirstChild(rootItem, value));

}

void UIDesignerFrame::UpDataProjectImportView()
{
	m_pImportPieceView->DeleteAllItems();
	wxTreeItemId rootItem = m_pImportPieceView->AddRoot(wxT("ImportPiece"));

	UIImagePieceView::TM_PIECE& ImageMap = m_pImagePieceView->GetPieceMap();
	for (UIImagePieceView::TM_PIECE::iterator it = ImageMap.begin(); it != ImageMap.end(); ++it)
	{
		UIImagePieceView::PIECEVIEW_INFO& pieceInfo = it->second;
		m_pImportPieceView->AppendItem(rootItem, pieceInfo.StrImage);
	}
	m_pImportPieceView->ExpandAll();

	wxTreeItemIdValue value;
	if(ImageMap.empty()) return;
	m_pImportPieceView->SelectItem(m_pProjectViewImage->GetFirstChild(rootItem, value));
}
void UIDesignerFrame::UpdateImagePieceView(const UIImagePieceDocument::PIECE_INFO* pPieceInfo)
{
	if (pPieceInfo)
	{
		const wxString& strImage = m_pImagePieceDocument->FindImage(pPieceInfo->nImageID);
		m_pImagePieceView->LoadImageFromFile(strImage);
	}
	m_pImagePieceView->SetSelectedPiece(pPieceInfo);
}


void UIDesignerFrame::OnFileNew(wxCommandEvent& event)
{
	// TODO: 
	UINewImagePieceView NewImagePiece(this,ID_NEWIMAGEPIECE);
	if(NewImagePiece.ShowModal() == wxID_OK)
	{
		m_pImagePieceDocument->NewFile(NewImagePiece.GetValue());
		m_pOutputView->AppendText("Add The New Xml File :" + NewImagePiece.GetValue() + "\n");
		UpdateProjectView();
		UpDateProjectImageView();
	}
}

void UIDesignerFrame::OnFileOpen(wxCommandEvent& event)
{
	wxFileDialog dialog(this, wxT("Choose a file"), wxEmptyString, wxEmptyString, wxT("XML files (*.xml)|*.xml"), wxFD_DEFAULT_STYLE);
	if (dialog .ShowModal() == wxID_OK)
	{
		wxString strPath = dialog.GetPath();
		m_pImagePieceDocument->OpenFile(strPath);
		UpdateProjectView();
		UpDateProjectImageView();
	}
}

void UIDesignerFrame::OnFileSave(wxCommandEvent& event)
{
	if (m_pImagePieceDocument && !m_pImagePieceDocument->GetFileName().IsEmpty())
	{
		m_pImagePieceDocument->SaveFile(m_pImagePieceDocument->GetFileName());
	}
	m_pImagePieceView->SaveImage();
}

void UIDesignerFrame::OnFileClose(wxCommandEvent& event)
{
	wxMessageDialog Dialog(NULL,"Don't you want to close the file",wxEmptyString, wxNO_DEFAULT|wxYES_NO);
	if(Dialog.ShowModal() != wxID_YES)
		return;
	if(m_pImagePieceDocument->GetImageMap().size() != 0)
	{
		wxMessageDialog MessageDialog(NULL,"Don't you want to save the file",wxEmptyString, wxNO_DEFAULT|wxYES_NO);
		if(MessageDialog.ShowModal() == wxID_YES)
				m_pImagePieceDocument->SaveFile(m_pImagePieceDocument->GetFileName());		
		m_pImagePieceDocument->Clear();
		m_pImagePieceView->ClearImportPiece();
		UpdateProjectView();
		UpDateProjectImageView();
		UpDataProjectImportView();
	}
}

void UIDesignerFrame::OnExit(wxCommandEvent& event)
{
	Destroy();
}

void UIDesignerFrame::OnImport(wxCommandEvent& event)
{
	if(m_pImagePieceDocument->GetImageMap().size() == 0) return;
	UIImportPieceView dialog(NULL);
	if(dialog.ShowModal() == wxID_OK)
	{
		wxString strFileName = dialog.GetFilePath();
		int nImageID = dialog.GetImageID();
		wxBitmap* pBitMap = new wxBitmap();
		if(!pBitMap->LoadFile(strFileName, wxBITMAP_TYPE_PNG))
		{
			SAFE_DELETE(pBitMap);
			return;
		}
		UIImagePieceView::PIECEVIEW_INFO PieceInof;
		UIImagePieceDocument::TM_IMAGE_INFO::iterator it  = m_pImagePieceDocument->GetImageMap().find(nImageID);
		PieceInof.StrBackGroundImage = it->second.strFile;
		PieceInof.pBitMap = pBitMap;
		PieceInof.StrImage = strFileName;
		wxMemoryDC* MenDc = new wxMemoryDC();
		MenDc->SelectObject(*pBitMap);
		PieceInof.pMemDC = MenDc;
		wxRect rect;
		rect.x = 0;
		rect.y = 0;
		rect.width = pBitMap->GetWidth();
		rect.height = pBitMap->GetHeight();
		PieceInof.rect = rect;
		m_pImagePieceView->AddImportPiece(PieceInof);
		UpDataProjectImportView();
	}
}
void UIDesignerFrame::OnLayoutMoveLeft(wxCommandEvent& event)
{
	m_pImagePieceView->MoveRelative(-1, 0);
}

void UIDesignerFrame::OnLayoutMoveRight(wxCommandEvent& event)
{
	m_pImagePieceView->MoveRelative(1, 0);
}

void UIDesignerFrame::OnLayoutMoveUp(wxCommandEvent& event)
{
	m_pImagePieceView->MoveRelative(0, -1);
}

void UIDesignerFrame::OnLayoutMoveDown(wxCommandEvent& event)
{
	m_pImagePieceView->MoveRelative(0, 1);
}

void UIDesignerFrame::OnViewZoom100(wxCommandEvent& event)
{
	m_pImagePieceView->Zoom(UIImagePieceView::ZOOM_MIN);
}

void UIDesignerFrame::OnViewZoomIn(wxCommandEvent& event)
{
	m_pImagePieceView->ZoomIn();
}

void UIDesignerFrame::OnViewZoomOut(wxCommandEvent& event)
{
	m_pImagePieceView->ZoomOut();

}

void UIDesignerFrame::OnProjectPieceItemSelChanged(wxTreeEvent& event)
{
	m_CurPieceTreeItemId = event.GetItem();
	wxString strItemID = m_pProjectViewPiece->GetItemText(m_CurPieceTreeItemId);

	UIImagePieceDocument::PIECE_INFO* pPieceInfo = m_pImagePieceDocument->FindPieceInfo(strItemID);
	if (!pPieceInfo) return;
	UpdateImagePieceView(pPieceInfo);
	UpDatePieceProterty(*pPieceInfo);
}
void UIDesignerFrame::OnPiecePropertyGridChange(wxPropertyGridEvent &event)
{
	if(!m_CurPieceTreeItemId) return;
	wxString strItemID = m_pProjectViewPiece->GetItemText(m_CurPieceTreeItemId);
	UIImagePieceDocument::PIECE_INFO* pPieceInfo = m_pImagePieceDocument->FindPieceInfo(strItemID);
	if (!pPieceInfo) return;
	pPieceInfo->strID = m_pProtertyStrID->GetValue().GetString();
	pPieceInfo->rect.x = m_pProtertyX->GetValue().GetInteger();
	pPieceInfo->rect.y = m_pProtertyY->GetValue().GetInteger();
	pPieceInfo->rect.width = m_pProtertyWidth->GetValue().GetInteger();
	pPieceInfo->rect.height = m_pProtertyHight->GetValue().GetInteger();
	UpdateImagePieceView(pPieceInfo);
}

void UIDesignerFrame::UpDatePieceProterty(const UIImagePieceDocument::PIECE_INFO& PieceInfo)
{
	m_pProtertyStrID->SetValue(PieceInfo.strID);
	m_pProtertyX->SetValue(PieceInfo.rect.x);
	m_pProtertyY->SetValue(PieceInfo.rect.y);
	m_pProtertyWidth->SetValue(PieceInfo.rect.width);
	m_pProtertyHight->SetValue(PieceInfo.rect.height);
}

void UIDesignerFrame::OnProjectPieceRightClick(wxTreeEvent& event)
{
	 m_CurPieceTreeItemId = event.GetItem();
	 wxPoint clientpt = event.GetPoint();
	 wxMenu menu;
	 menu.Append(ID_ADDPIECEMENU,wxT("&Add Piece"));
	 menu.Append(ID_DELETE_PIECE, wxT("&Delete Piece"));
	 menu.Append(ID_CUT_PIECE, wxT("&Cut Piece"));
	 m_pProjectViewPiece->PopupMenu(&menu, clientpt);
}

void UIDesignerFrame::OnProjectImageItemSelChanged(wxTreeEvent& event)
{
	//TODO: update the 
	m_CurImageTreeItemId = event.GetItem();
	wxString strItemID = m_pProjectViewPiece->GetItemText(m_CurImageTreeItemId);
	int KeyValue = m_pImagePieceDocument->GetImageMapKeyValue(strItemID);
	UIImagePieceDocument::TM_IMAGE_INFO::iterator it = m_pImagePieceDocument->GetImageMap().find(KeyValue);
	if(it != m_pImagePieceDocument->GetImageMap().end())
		UpdateImageProterty(it->second);
}

void UIDesignerFrame::UpdateImageProterty(const UIImagePieceDocument::IMAGE_INFO& ImageInfo)
{
	m_pImageFileNameProterty->SetValue(ImageInfo.strFile);
	m_pImageIDProterty->SetValue(ImageInfo.nID);
}

void UIDesignerFrame::OnImagePropertyGridChange(wxPropertyGridEvent& event)
{
	//TODO:
}
void UIDesignerFrame::OnProjectImageViewRightClick(wxTreeEvent& event)
{
	m_CurImageTreeItemId = event.GetItem();
	wxPoint clientpt = event.GetPoint();
	wxMenu menu;
	menu.Append(ID_ADDIMAGEMENU,wxT("&Add Image"));
	menu.Append(ID_DELETE_IMAGE, wxT("&Delete Image"));
	m_pProjectViewImage->PopupMenu(&menu, clientpt);
}


void UIDesignerFrame::OnImagePieceChanged(wxImagePieceEvent& event)
{
	const UIImagePieceDocument::PIECE_INFO& pieceInfo = event.GetPieceInfo();
	m_pImagePieceDocument->UpdateImagePiece(pieceInfo);
}

void UIDesignerFrame::OnAddPieceInfo(wxCommandEvent& event)
{
	if(m_pImagePieceDocument->GetImageMap().size() ==0) 
	{
		m_pOutputView->AppendText("Error: Don't have any Image\n");
		return;
	}
	AddImageDialog pAddImage(this, ID_ADDIMAGE, wxT("Add Image"));

	if(pAddImage.ShowModal() == wxAPPLY)
	{
		UIImagePieceDocument::PIECE_INFO vlaue = pAddImage.GetValue();
		if(m_pImagePieceDocument->FindImage(vlaue.nImageID) == wxEmptyString)
			return;
		m_pImagePieceDocument->AddPieceInfo(vlaue);
		UpdateProjectView();
	}
	event.Skip();
}

void UIDesignerFrame::OnDeletePieceInfo(wxCommandEvent& event)
{
	wxMessageDialog Dialog(NULL, "Don't you want to delete it!", wxEmptyString, wxNO_DEFAULT| wxYES_NO);
	if(Dialog.ShowModal() != wxID_YES) return;
	wxString strItemID = m_pProjectViewPiece->GetItemText(m_CurPieceTreeItemId);

	if(!m_pImagePieceDocument->GetPieceInfoMap().erase(strItemID))
		m_pOutputView->AppendText("Error: Failed delete" + strItemID + "\n");
	UpdateProjectView();
	event.Skip();
}
void UIDesignerFrame::OnCutPiece(wxCommandEvent& event)
{
	wxString strItemID = m_pProjectViewPiece->GetItemText(m_CurPieceTreeItemId);
	UIImagePieceDocument::TM_PIECE_INFO::iterator PieceIt =  m_pImagePieceDocument->GetPieceInfoMap().find(strItemID);
	
	if(PieceIt == m_pImagePieceDocument->GetPieceInfoMap().end()) return;
	UIImagePieceDocument::TM_IMAGE_INFO::iterator ImageIt  = m_pImagePieceDocument->GetImageMap().find((*PieceIt).second.nImageID);
	if(ImageIt == m_pImagePieceDocument->GetImageMap().end()) return;
	wxString StrBackImageFileName = (*ImageIt).second.strFile;
	
	UIImagePieceView::TM_BITMAP_CACHE::iterator BitMapIt = m_pImagePieceView->GetBitCacheMap().find(StrBackImageFileName);
	if( BitMapIt == m_pImagePieceView->GetBitCacheMap().end()) return;

	wxImage BackGroundImage(BitMapIt->second->ConvertToImage());
	wxImage SubImage = BackGroundImage.GetSubImage(PieceIt->second.rect);
	wxBitmap* pNewBitMap = new wxBitmap(SubImage,32 );
	wxMemoryDC* pMenDc = new wxMemoryDC();
	pMenDc->SelectObject(*pNewBitMap);
	
	UIImagePieceView::PIECEVIEW_INFO PieceInof;
	PieceInof.pBitMap = pNewBitMap;
	PieceInof.pMemDC = pMenDc;
	PieceInof.rect = PieceIt->second.rect;
	PieceInof.StrBackGroundImage = StrBackImageFileName;
	PieceInof.StrImage = strItemID;
	m_pImagePieceView->AddImportPiece(PieceInof);
	UpDataProjectImportView();
	
	//Modify BackGround
	int nStartX = PieceInof.rect.x;
	int nEndX = nStartX + PieceInof.rect.width;
	int nStartY = PieceInof.rect.y;
	int nEndY = nStartY + PieceInof.rect.height;

	for(int x = nStartX; x < nEndX; x++)
	{	
		for(int y = nStartY; y < nEndY; y++)
		{
			BackGroundImage.SetAlpha(x, y, 0);
		}
	}

	delete BitMapIt->second;
	m_pImagePieceView->GetBitCacheMap().erase(StrBackImageFileName);
	wxBitmap* pNewBitmap = new wxBitmap(BackGroundImage, 32);

	m_pImagePieceView->GetBitCacheMap().insert(std::make_pair(StrBackImageFileName, pNewBitmap));
	//Modify the next code; add the UIImagePieceView function to frush the imageView
	//m_pImagePieceView->LoadImageFromFile(m_pImagePieceView->GetBackFileName());
	m_pImagePieceView->UpdateBitMapCache();
	//Delete the Cur ImagePiece Item;
	m_pImagePieceDocument->GetPieceInfoMap().erase(strItemID);
	UpdateProjectView();
}
void UIDesignerFrame::OnAddImageInfo(wxCommandEvent& event)
{
	UIAddImageInfoView uiAddImage(this, ID_ADDPIECE);
	if(uiAddImage.ShowModal()== wxOK)
	{
		UIImagePieceDocument::IMAGE_INFO ImageInfo = uiAddImage.GetValue();
		if(m_pImagePieceDocument->FindImage(ImageInfo.nID) != wxEmptyString)
			m_pOutputView->AppendText("Error:Have the same ID\n");
		m_pImagePieceDocument->AddImageInfo(ImageInfo);
		UpDateProjectImageView();
	}
}

void UIDesignerFrame::OnDeleteImageInfo(wxCommandEvent& event)
{
	wxMessageDialog Dialog(NULL, "Don't you want to delete it!", wxEmptyString, wxNO_DEFAULT| wxYES_NO);
	if(Dialog.ShowModal() != wxID_YES) return;
	wxString strItemID = m_pProjectViewPiece->GetItemText(m_CurImageTreeItemId);
	int KeyValue = m_pImagePieceDocument->GetImageMapKeyValue(strItemID);
	if(!m_pImagePieceDocument->GetImageMap().erase(KeyValue))
		m_pOutputView->AppendText("Error: Failed delete" + strItemID + "\n");
	UpDateProjectImageView();
	event.Skip();
}

void UIDesignerFrame::OnProjectImportItemSleChanged(wxTreeEvent& event)
{
	m_CurImportTreeItemId = event.GetItem();
	wxString strItemID = m_pImportPieceView->GetItemText(m_CurImportTreeItemId);
	UIImagePieceView::TM_PIECE::iterator pieceInof = m_pImagePieceView->GetPieceMap().find(strItemID);
	if(pieceInof == m_pImagePieceView->GetPieceMap().end()) return;
	m_pImportPieceFileName->SetValue((*pieceInof).second.StrImage);
	m_pImageID->SetValue(m_pImagePieceDocument->GetImageMapKeyValue((*pieceInof).second.StrBackGroundImage));
	m_pImportPieceX->SetValue((*pieceInof).second.rect.x);
	m_pImportPieceY->SetValue((*pieceInof).second.rect.y);
	m_pImagePieceView->Update();
	m_pImagePieceView->SetSelectedPiece(strItemID);
}

void UIDesignerFrame::OnProjectImportRightClick(wxTreeEvent& event)
{
	m_CurImportTreeItemId = event.GetItem();
	wxPoint clientpt = event.GetPoint();
	wxMenu menu;
	menu.Append(IDC_DELETE_IMPORTPIECE, wxT("&Delete"));
	menu.Append(IDC_LOAD_IMPORTPIECE, wxT("&Load"));
	m_pImportPieceView->PopupMenu(&menu, clientpt);
}

void UIDesignerFrame::OnImportPropertyGridChange(wxPropertyGridEvent& event)
{
	wxString strItemID = m_pImportPieceView->GetItemText(m_CurImportTreeItemId);
	UIImagePieceView::TM_PIECE::iterator pieceInof = m_pImagePieceView->GetPieceMap().find(strItemID);
	if(pieceInof == m_pImagePieceView->GetPieceMap().end()) return;

	int ImageID = m_pImageID->GetValue().GetInteger();
	int nX = m_pImportPieceX->GetValue().GetInteger();
	int nY = m_pImportPieceY->GetValue().GetInteger();
	
	UIImagePieceDocument::TM_IMAGE_INFO::iterator it = m_pImagePieceDocument->GetImageMap().find(ImageID);
	if(it == m_pImagePieceDocument->GetImageMap().end()) return;
	
	
	pieceInof->second.StrBackGroundImage = it->second.strFile;
	pieceInof->second.rect.x = nX;
	pieceInof->second.rect.y = nY;
	m_pImagePieceView->Update();
	m_pImagePieceView->SetSelectedPiece(strItemID);
}

void UIDesignerFrame::OnDelteImportPiece(wxCommandEvent& event)
{
	wxMessageDialog Dialog(this, "Do you want to delete it!", wxEmptyString,  wxNO_DEFAULT| wxYES_NO);
	if(Dialog.ShowModal() != wxID_YES)return;
	wxString strItemID = m_pImportPieceView->GetItemText(m_CurImportTreeItemId);
	if(!m_pImagePieceView->GetPieceMap().erase(strItemID))
		m_pOutputView->AppendText("Failed delete " + strItemID);
	UpDataProjectImportView();
	m_pImagePieceView->Update();
}

void UIDesignerFrame::OnLoadImportPiece(wxCommandEvent& event)
{
	wxString strItemID = m_pImportPieceView->GetItemText(m_CurImportTreeItemId);
	UIImagePieceView::TM_PIECE::iterator pieceInof = m_pImagePieceView->GetPieceMap().find(strItemID);
	if(pieceInof == m_pImagePieceView->GetPieceMap().end()) return;
	wxString StrFileName = pieceInof->first;
	wxString Type = StrFileName.substr(StrFileName.size() - 4, 4);
	if(Type != ".png")
		StrFileName.Append(".png");
	wxImage Image(pieceInof->second.pBitMap->ConvertToImage());
	if(Image.SaveFile(StrFileName, wxBITMAP_TYPE_PNG))
	{
		wxMessageBox("Load " + StrFileName + " Success");
	}
}

void UIDesignerFrame::OnSortPiece(wxCommandEvent& event)
{
	CombinaPiece::SortPiece(m_pImagePieceDocument->GetPieceInfoMap(), m_pImagePieceView->GetBitCacheMap(), m_pImagePieceDocument->GetImageMap());
	UpdateProjectView();
	m_pImagePieceView->UpdateBitMapCache();
}