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

	EVT_TREE_ITEM_MENU(IDC_PROJECT, UIDesignerFrame::OnProjectRightClick)
	EVT_TREE_ITEM_MENU(IDC_PROJECTIMAGE, UIDesignerFrame::OnProjectImageViewRightClick)
	//evt_tr(IDC_PROJECT, UIDesignerFrame::OnProjectRightClick)
	EVT_TREE_SEL_CHANGED(IDC_PROJECT, UIDesignerFrame::OnProjectItemSelChanged)
	EVT_IMAGE_PIECE_CHANGED(IDC_INPUT_VIEW, UIDesignerFrame::OnImagePieceChanged)
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
	m_pProjectView = NULL;
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
	m_pProjectView = new wxTreeCtrl( this, IDC_PROJECT, wxDefaultPosition, wxSize(200, 100), wxTR_SINGLE );
	m_auiManager.AddPane(m_pProjectView, wxAuiPaneInfo()
		.Name(_T("PieceView")).CaptionVisible(true).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));

	m_pProjectViewImage = new wxTreeCtrl( this, IDC_PROJECTIMAGE, wxDefaultPosition, wxSize(200, 100), wxTR_SINGLE );
	m_auiManager.AddPane(m_pProjectViewImage, wxAuiPaneInfo()
		.Name(_T("ImageView")).CaptionVisible(true).CloseButton(false).DestroyOnClose(false).Resizable(true).Floatable(false));
}

void UIDesignerFrame::CreatePropertyView()
{
	wxPropertyGrid* pProperty = new wxPropertyGrid(this, IDC_PROPERTY, wxDefaultPosition, wxDefaultSize, wxPG_SPLITTER_AUTO_CENTER|wxNO_BORDER);
	pProperty->Append(new wxStringProperty("String Property", wxPG_LABEL));
	pProperty->Append(new wxIntProperty("Int Property", wxPG_LABEL));
	pProperty->Append(new wxBoolProperty("Bool Property", wxPG_LABEL));

	m_auiManager.AddPane(pProperty, wxAuiPaneInfo()
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

void UIDesignerFrame::CreateInputView()
{
	m_pImagePieceView = new UIImagePieceView(this, IDC_INPUT_VIEW, wxDefaultPosition, wxDefaultSize, wxNO_BORDER);
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
	m_pProjectView->DeleteAllItems();
	wxTreeItemId rootItem = m_pProjectView->AddRoot(wxT("ImagePiece"));

	const UIImagePieceDocument::TM_PIECE_INFO& pieceInfoMap = m_pImagePieceDocument->GetPieceInfoMap();
	for (UIImagePieceDocument::TM_PIECE_INFO::const_iterator it = pieceInfoMap.begin(); it != pieceInfoMap.end(); ++it)
	{
		const UIImagePieceDocument::PIECE_INFO& pieceInfo = it->second;
		m_pProjectView->AppendItem(rootItem, pieceInfo.strID);
	}
	m_pProjectView->ExpandAll();

	wxTreeItemIdValue value;
	if(pieceInfoMap.empty()) return;
	m_pProjectView->SelectItem(m_pProjectView->GetFirstChild(rootItem, value));
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
}

void UIDesignerFrame::OnFileClose(wxCommandEvent& event)
{
	if(m_pImagePieceDocument->GetImageMap().size() != 0)
	{
		UITipsDialog uiTipsDialog(this,ID_TIPS_DIALOG);
		if(uiTipsDialog.ShowModal() == wxID_YES)
			m_pImagePieceDocument->SaveFile(m_pImagePieceDocument->GetFileName());
		m_pImagePieceDocument->Clear();
		UpdateProjectView();
		UpDateProjectImageView();
	}

}

void UIDesignerFrame::OnExit(wxCommandEvent& event)
{
	Destroy();
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

void UIDesignerFrame::OnProjectItemSelChanged(wxTreeEvent& event)
{
	m_CurTreeItemId = event.GetItem();
	wxString strItemID = m_pProjectView->GetItemText(m_CurTreeItemId);

	const UIImagePieceDocument::PIECE_INFO* pPieceInfo = m_pImagePieceDocument->FindPieceInfo(strItemID);
	if (!pPieceInfo) return;
	UpdateImagePieceView(pPieceInfo);	
}

void UIDesignerFrame::OnImagePieceChanged(wxImagePieceEvent& event)
{
	const UIImagePieceDocument::PIECE_INFO& pieceInfo = event.GetPieceInfo();
	m_pImagePieceDocument->UpdateImagePiece(pieceInfo);
}

void UIDesignerFrame::OnProjectRightClick(wxTreeEvent& event)
{
	 m_CurTreeItemId = event.GetItem();
	 wxPoint clientpt = event.GetPoint();
	 wxMenu menu;
	 menu.Append(ID_ADDPIECEMENU,wxT("&Add Piece"));
	 menu.Append(ID_DELETE_PIECE, wxT("&Delete Piece"));
	 m_pProjectView->PopupMenu(&menu, clientpt);
}


void UIDesignerFrame::OnProjectImageViewRightClick(wxTreeEvent& event)
{
	m_CurTreeItemId = event.GetItem();
	wxPoint clientpt = event.GetPoint();
	wxMenu menu;
	menu.Append(ID_ADDIMAGEMENU,wxT("&Add Image"));
	menu.Append(ID_DELETE_IMAGE, wxT("&Delete Image"));
	m_pProjectViewImage->PopupMenu(&menu, clientpt);
}
void UIDesignerFrame::OnAddPieceInfo(wxCommandEvent& event)
{
	if(m_pImagePieceDocument->GetImageMap().size() ==0) 
	{
		m_pOutputView->AppendText("Error: Don't hava any Image\n");
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
	wxString strItemID = m_pProjectView->GetItemText(m_CurTreeItemId);

	if(!m_pImagePieceDocument->GetPieceInfoMap().erase(strItemID))
		m_pOutputView->AppendText("Error: Failed delete" + strItemID + "\n");
	UpdateProjectView();
	event.Skip();
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
	wxString strItemID = m_pProjectView->GetItemText(m_CurTreeItemId);
	int KeyValue = m_pImagePieceDocument->GetImageMapKeyValue(strItemID);
	if(!m_pImagePieceDocument->GetImageMap().erase(KeyValue))
		m_pOutputView->AppendText("Error: Failed delete" + strItemID + "\n");
	UpDateProjectImageView();
	event.Skip();
}
