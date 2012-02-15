/*!
 * \file DesignerFrame.h
 * \date 2-14-2012 1:21:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DESIGNERFRAME_H__
#define __DESIGNERFRAME_H__

#include <wx/frame.h>
#include <wx/aui/aui.h>
#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include "editor/BaseEditor.h"

class DesignerFrame : public wxFrame
{
public:
	enum CONTROL_ID
	{
		ID_UIDESIGNERFRAME = 10000,

		IDM_EDIT_UNDO,
		IDM_EDIT_REDO,
		IDM_EDIT_COPY,
		IDM_EDIT_CUT,
		IDM_EDIT_PAST,
		IDM_EDIT_DELETE,

		IDM_VIEW_GRID,
		IDM_TOOL_PREFERENCES,
		IDM_HELP_SUPPORT,
		IDM_HELP_ABOUT,

 		IDC_TOOLBAR,
		IDC_NOTEBOOK_LIST,
		IDC_NOTEBOOK_EDITOR,
		IDC_PIECE_LIST,
		IDC_IMAGE_LIST,
		IDC_BITMAP_STYLE_LIST,
		IDC_NINE_GRID_STYLE_LIST,
		IDC_COLOR_STYLE_LIST,
		IDC_CLIP_BITMAP_STYLE_LIST,

		IDC_PROPERTY,
		IDC_IMAGE_PIECE_EDITOR_VIEW,
		IDC_BITMAP_STYLE_EDITOR_VIEW,
		IDC_NINE_GRID_STYLE_EDITOR_VIEW,
		IDC_COLOR_STYLE_EDITOR_VIEW,
		IDC_CLIP_BITMAP_STYLE_EDITOR_VIEW,
		IDC_OUTPUT_VIEW,
	};

	enum EDITOR
	{
		EDITOR_IMAGE_PIECE = 0,
		EDITOR_BITMAP_STYLE,
		EDITOR_NINE_GRID_STYLE,
		EDITOR_COLOR_STYLE,
		EDITOR_CLIP_BITMAP_STYLE,
		NUM_EDITOR,
	};

	enum PROPERTY_TYPE
	{
		PT_UNKNOWN = 0,
		PT_IMAGE,
		PT_PIECE,
		PT_BITMAP_STYLE,
		PT_NINE_GRID_STYLE,
		PT_COLOR_STYLE,
		PT_CLIP_BITMAP_STYLE,
	};

public:
	DECLARE_DYNAMIC_CLASS(DesignerFrame)
	DECLARE_EVENT_TABLE()

public:
	DesignerFrame();
	virtual ~DesignerFrame();

	static DesignerFrame& GetInstance();

	void SetCurrPropertyType(PROPERTY_TYPE eType);
	PROPERTY_TYPE GetCurrPropertyType() const;

private:
	void Init();
	void Release();

	void CreateControls();
	void CreateMenu();
	void CreateToolbar();
	void CreatePropertyView();
	void CreateListView();
	void CreateEditorView();
	void CreateOutputView();

	void OnFileOpen(wxCommandEvent& event);
	void OnFileSave(wxCommandEvent& event);
	void OnFileClose(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

	void OnViewZoom100(wxCommandEvent& event);
	void OnViewZoomIn(wxCommandEvent& event);
	void OnViewZoomOut(wxCommandEvent& event);

	void OnImagePieceListSelected(wxTreeEvent& event);
	void OnImageListSelected(wxTreeEvent& event);
	void OnBitmapStyleListSelected(wxTreeEvent& event);
	void OnNineGridStyleListSelected(wxTreeEvent& event);
	void OnColorStyleListSelected(wxTreeEvent& event);
	void OnClipBitmapStyleListSelected(wxTreeEvent& event);

	void OnPropertyGridChanged(wxPropertyGridEvent& event);

private:
	static DesignerFrame* m_pDesignerFrame;

	wxAuiManager m_auiManager;

	wxTextCtrl* m_pOutputView;

	PROPERTY_TYPE m_eCurrPropertyType;
	wxPropertyGrid* m_pPropertyGrid;

	wxNotebook* m_pEditorNotebook;
	BaseEditor* m_pEditors[NUM_EDITOR];

};
#endif // __DESIGNERFRAME_H__
