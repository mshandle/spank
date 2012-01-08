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

#include "UIImagePieceEditor.h"
#include "UIImagePieceDocument.h"
#include "wxImagePieceEvent.h"

class UIDesignerFrame : public wxFrame
{
public:
	enum CONTROL_ID
	{
		ID_UIDESIGNERFRAME = 10000,
		ID_EDIT_UNDO,
		ID_EDIT_REDO,
		ID_EDIT_COPY,
		ID_EDIT_CUT,
		ID_EDIT_PAST,
		ID_EDIT_DELETE,
		ID_LAYOUT_ALIGN,
		ID_LAYOUT_ALIGN_LEFT,
		ID_LAYOUT_ALIGN_RIGHT,
		ID_LAYOUT_ALIGN_TOP,
		ID_LAYOUT_ALIGN_BOTTOM,
		ID_LAYOUT_ALIGN_CENTER,
		ID_LAYOUT_ALIGN_MIDDLE,
		ID_LAYOUT_MOVE,
		ID_LAYOUT_MOVE_LEFT,
		ID_LAYOUT_MOVE_RIGHT,
		ID_LAYOUT_MOVE_UP,
		ID_LAYOUT_MOVE_DOWN,
		ID_VIEW_GRID,
		ID_TOOL_PREFERENCES,
		ID_HELP_SUPPORT,
		ID_HELP_ABOUT,
		ID_TOOLBAR,
		ID_ADDIMAGE,
		ID_ADDPIECE,
		ID_NEWIMAGEPIECE,
		ID_NEWDILOG,
		ID_ADDPIECEMENU,
		ID_ADDIMAGEMENU,
		ID_DELETE_IMAGE,
		ID_DELETE_PIECE,
		ID_CUT_PIECE,
		ID_TIPS_DIALOG,

		IDC_PROJECT_NOTEBOOK,
		IDC_PROJECT_IMAGE_PIECE,
		IDC_PROJECT_TEXTURE_LIST,
		IDC_PROJECT_IMAPORTED,

		IDC_PROPERTYPIECE,
		IDC_INPUT_VIEW,
		IDC_OUTPUT_VIEW,
		IDC_PROPERTYIMAGE,
		IDC_UIIMAGE_VIEW,
		IDC_IMPORT_PIECE,
		IDC_IMPORT_PROPERTY,
		IDC_DELETE_IMPORTPIECE,
		IDC_LOAD_IMPORTPIECE,
		IDC_SORT_PIECE,
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

	void OnProjectImagePieceSelChanged(wxTreeEvent& event);
	void OnProjectImagePieceContextMenu(wxTreeEvent& event);
	
	void OnProjectTextureListSelChanged(wxTreeEvent& event);
	void OnProjectTextureListContextMenu(wxTreeEvent& event);
	void OnImagePieceChanged(wxImagePieceEvent& event);

	void OnPiecePropertyGridChange(wxPropertyGridEvent &event);
	void UpDatePieceProterty(const UIImagePieceDocument::PIECE_INFO& PieceInfo);

	void OnImagePropertyGridChange(wxPropertyGridEvent& event);
	void UpdateImageProterty(const UIImagePieceDocument::IMAGE_INFO& ImageInfo);
	
	void OnProjectImportedSelChanged(wxTreeEvent& event);
	void OnProjectImportedContextMenu(wxTreeEvent& event);
	void UpdateImportPieceProterty(const UIImagePieceEditor::PIECE_VIEW_INFO& PieceInfo);
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

	// project relate
	wxNotebook* m_pProjectNotebook;
	wxTreeCtrl* m_pProjectImagePiece;
	wxTreeCtrl* m_pProjectTextureList;
	wxTreeCtrl* m_pProjectImported;

	UIImagePieceEditor* m_pImagePieceView;
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
