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

class UIDesignerFrame : public wxFrame
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
		IDC_NOTEBOOK,
		IDC_IMAGE_PIECE_LIST,
		IDC_IMAGE_LIST,

		IDC_PROPERTY,
		IDC_EDITOR_VIEW,
		IDC_OUTPUT_VIEW,
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
	void CreateEditorView();
	void CreateOutputView();

	void UpdateImagePieceView();
	void UpdateImageListView();
	void UpdateImagePieceEditor(const PieceInfo* pPieceInfo);
	
	void OnFileOpen(wxCommandEvent& event);
	void OnFileSave(wxCommandEvent& event);
	void OnFileClose(wxCommandEvent& event);
	void OnExit(wxCommandEvent& event);

	void OnViewZoom100(wxCommandEvent& event);
	void OnViewZoomIn(wxCommandEvent& event);
	void OnViewZoomOut(wxCommandEvent& event);

	void OnImagePieceListSelected(wxTreeEvent& event);
	void OnImageListSelected(wxTreeEvent& event);

private:
	wxAuiManager m_auiManager;

	wxNotebook* m_pNotebookView;
	wxTreeCtrl* m_pImagePieceListView;
	wxTreeCtrl* m_pImageListView;

	UIImagePieceEditor* m_pImagePieceEditor;
	UIImagePieceDocument* m_pImagePieceDocument;

	wxTextCtrl* m_pOutputView;
	wxPropertyGrid* m_pPropertyGrid;

};
#endif // __UIDESIGNERFRAME_H__
