/*!
 * \file ImagePieceEditor.h
 * \date 2-14-2012 1:24:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGEPIECEEDITOR_H__
#define __IMAGEPIECEEDITOR_H__

#include "BaseEditor.h"
#include "../document/PieceInfo.h"
#include "../document/ImageInfo.h"

class ImagePieceEditor : public BaseEditor
{
public:
	ImagePieceEditor();
	ImagePieceEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual ~ImagePieceEditor();

	static ImagePieceEditor& GetInstance();

	void SetSelection(PieceInfo* pPieceInfo);
	PieceInfo* GetSelection() const;

	bool SetImage(ImageInfo* pImageInfo);
	ImageInfo* GetImage() const;

	virtual wxSize CalculateVirtualSize();
	virtual void Draw(wxDC& dc);
	virtual void OnLButtonDown(const wxPoint& pos);

private:
	void Init();
	void Release();

	void DrawSelection(wxDC& dc);

private:
	static ImagePieceEditor* m_pImagePieceEditor;
	wxMemoryDC m_memDC;
	PieceInfo* m_pPieceInfo;
	ImageInfo* m_pImageInfo;

};
#endif // __IMAGEPIECEEDITOR_H__
