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
#include <wx/propgrid/property.h>

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
		IDC_EDITOR_VIEW,
		IDC_OUTPUT_VIEW,
	};

public:
	DECLARE_DYNAMIC_CLASS(DesignerFrame)
	DECLARE_EVENT_TABLE()

public:
	DesignerFrame();
	virtual ~DesignerFrame();

	static DesignerFrame& GetInstance();

private:
	void Init();

	void CreateControls();
	void CreateMenu();
	void CreateToolbar();
	void CreateListView();
	void CreatePropertyView();
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

private:
	static DesignerFrame* m_pDesignerFrame;

	wxAuiManager m_auiManager;

	wxTextCtrl* m_pOutputView;
	wxPropertyGrid* m_pPropertyGrid;

};
#endif // __DESIGNERFRAME_H__
