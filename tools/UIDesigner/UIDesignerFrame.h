/*!
 * \file UIDesignerFrame.h
 * \date 8-31-2011 13:11:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UIDESIGNERFRAME_H__
#define __UIDESIGNERFRAME_H__

#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/treectrl.h>
#include <wx/propgrid/property.h>

#include "UIImagePieceView.h"
#include "UIImagePieceDocument.h"
#include "wxImagePieceEvent.h"

class UIDesignerFrame : public wxFrame
{
public:
	enum CONTROL_ID
	{
		ID_UIDESIGNERFRAME = 10000,
		ID_EDIT_UNDO = 10048,
		ID_EDIT_REDO = 10049,
		ID_EDIT_COPY = 10025,
		ID_EDIT_CUT = 10026,
		ID_EDIT_PAST = 10027,
		ID_EDIT_DELETE = 10050,
		ID_LAYOUT_ALIGN = 10051,
		ID_LAYOUT_ALIGN_LEFT = 10028,
		ID_LAYOUT_ALIGN_RIGHT = 10029,
		ID_LAYOUT_ALIGN_TOP = 10030,
		ID_LAYOUT_ALIGN_BOTTOM = 10031,
		ID_LAYOUT_ALIGN_CENTER = 10032,
		ID_LAYOUT_ALIGN_MIDDLE = 10033,
		ID_LAYOUT_MOVE = 10052,
		ID_LAYOUT_MOVE_LEFT = 10052,
		ID_LAYOUT_MOVE_RIGHT = 10035,
		ID_LAYOUT_MOVE_UP = 10036,
		ID_LAYOUT_MOVE_DOWN = 10037,
		ID_VIEW_GRID = 10038,
		ID_TOOL_PREFERENCES = 10042,
		ID_HELP_SUPPORT = 10043,
		ID_HELP_ABOUT = 10044,
		ID_TOOLBAR = 10018,
		IDC_PROJECT = 10003,
		IDC_PROPERTYPIECE = 10002,
		
		IDC_INPUT_VIEW = 10004,
		IDC_OUTPUT_VIEW = 10001,
		ID_ADDIMAGE = 10060,
		ID_ADDPIECE = 10061,
		ID_NEWIMAGEPIECE = 10062,
		ID_NEWDILOG = 10063,
		ID_ADDPIECEMENU = 10064,
		ID_ADDIMAGEMENU = 10065,
		ID_DELETE_IMAGE = 10066,
		ID_DELETE_PIECE = 10067,
		ID_CUT_PIECE = 10075,
		ID_TIPS_DIALOG = 10068,
		IDC_PROJECTIMAGE = 10069,
		IDC_PROPERTYIMAGE = 10070,
		IDC_UIIMAGE_VIEW = 10071,
		IDC_IMPORT_PIECE = 10072,
		IDC_IMAPORT_PIECE_VIEW = 10073,
		IDC_IMPORT_PROPERTY = 10074,
		IDC_DELETE_IMPORTPIECE = 10100,
		IDC_LOAD_IMPORTPIECE = 10101,
		IDC_SORT_PIECE = 10102,
	};

public:
	DECLARE_DYNAMIC_CLASS(UIDesignerFrame)
	DECLARE_EVENT_TABLE()

public:
	UIDesignerFrame();
	virtual ~UIDesignerFrame();

private:
	void Init();

	void CreateControls();
	void CreateMenu();
	void CreateToolbar();
	void CreateProjectView();
	void CreatePropertyView();
	void CreateInputView();
	void CreateOutputView();

	void UpdateProjectView();
	void UpDateProjectImageView();
	void UpDataProjectImportView();

	void UpdateImagePieceView(const UIImagePieceDocument::PIECE_INFO* pPieceInfo);
	
	void OnFileNew(wxCommandEvent& event);
	void OnFileOpen(wxCommandEvent& event);
	void OnFileSave(wxCommandEvent& event);
	void OnFileClose(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);
	void OnImport(wxCommandEvent& event);

	void OnSortPiece(wxCommandEvent& event);
	void OnLayoutMoveLeft(wxCommandEvent& event);
	void OnLayoutMoveRight(wxCommandEvent& event);
	void OnLayoutMoveUp(wxCommandEvent& event);
	void OnLayoutMoveDown(wxCommandEvent& event);

	void OnViewZoom100(wxCommandEvent& event);
	void OnViewZoomIn(wxCommandEvent& event);
	void OnViewZoomOut(wxCommandEvent& event);

	void OnProjectPieceItemSelChanged(wxTreeEvent& event);
	void OnProjectPieceRightClick(wxTreeEvent& event);
	
	void OnProjectImageItemSelChanged(wxTreeEvent& event);
	void OnProjectImageViewRightClick(wxTreeEvent& event);
	void OnImagePieceChanged(wxImagePieceEvent& event);

	void OnPiecePropertyGridChange(wxPropertyGridEvent &event);
	void UpDatePieceProterty(const UIImagePieceDocument::PIECE_INFO& PieceInfo);

	void OnImagePropertyGridChange(wxPropertyGridEvent& event);
	void UpdateImageProterty(const UIImagePieceDocument::IMAGE_INFO& ImageInfo);
	
	void OnProjectImportItemSleChanged(wxTreeEvent& event);
	void OnProjectImportRightClick(wxTreeEvent& event);
	void UpdateImportPieceProterty(const UIImagePieceView::PIECEVIEW_INFO& PieceInfo);
	void OnImportPropertyGridChange(wxPropertyGridEvent& event);

	void OnAddImageInfo(wxCommandEvent& event);
	void OnDeleteImageInfo(wxCommandEvent& event);
	
	void OnAddPieceInfo(wxCommandEvent& event);
	void OnDeletePieceInfo(wxCommandEvent& event);
	void OnCutPiece(wxCommandEvent& event);
	void OnDelteImportPiece(wxCommandEvent& event);
	void OnLoadImportPiece(wxCommandEvent& event);
private:
	wxAuiManager m_auiManager;
	wxTreeCtrl* m_pProjectViewPiece;
	wxTreeCtrl* m_pProjectViewImage;
	wxTreeCtrl* m_pImportPieceView;
	UIImagePieceView* m_pImagePieceView;
	UIImagePieceDocument* m_pImagePieceDocument;

	wxTextCtrl* m_pOutputView;

	wxTreeItemId m_CurPieceTreeItemId;
	wxTreeItemId m_CurImageTreeItemId;
	wxTreeItemId m_CurImportTreeItemId;
	//Piece and Image proterty view point;
	wxPropertyGrid* m_pPieceProperty;
	wxPGProperty* m_pProtertyStrID;
	wxPGProperty* m_pProtertyX;
	wxPGProperty* m_pProtertyY;
	wxPGProperty* m_pProtertyWidth;
	wxPGProperty* m_pProtertyHight;

	wxPropertyGrid* m_pImageProperty;
	wxPGProperty* m_pImageFileNameProterty;
	wxPGProperty* m_pImageIDProterty;

	wxPropertyGrid* m_pImportPieceProperty;
	wxPGProperty* m_pImportPieceFileName;
	wxPGProperty* m_pImageID;
	wxPGProperty* m_pImportPieceX;
	wxPGProperty* m_pImportPieceY;

};
#endif // __UIDESIGNERFRAME_H__
