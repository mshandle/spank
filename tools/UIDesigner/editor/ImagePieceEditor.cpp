/*!
 * \file ImagePieceEditor.cpp
 * \date 2-14-2012 1:24:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImagePieceEditor.h"
#include "../document/ImagePieceDocument.h"
#include "../transformer/PieceListTransformer.h"
#include "../transformer/ImageListTransformer.h"

#define SAFE_DELETE(x) if (x) {delete (x); (x) = NULL;}

ImagePieceEditor* ImagePieceEditor::m_pImagePieceEditor = NULL;

ImagePieceEditor::ImagePieceEditor()
:BaseEditor()
{
	Init();
}

ImagePieceEditor::ImagePieceEditor(wxWindow *parent, wxWindowID winid, const wxPoint& pos /* = wxDefaultPosition */, const wxSize& size /* = wxDefaultSize */, long style /* = 0 */, const wxString& name /* = wxPanelNameStr */)
:BaseEditor(parent, winid, pos, size, style, name)
{
	Init();
}

ImagePieceEditor::~ImagePieceEditor()
{
	Release();
}

void ImagePieceEditor::Init()
{
	m_pImagePieceEditor = this;

	m_pPieceInfo = NULL;
	m_pImageInfo = NULL;
}

void ImagePieceEditor::Release()
{
	m_pImagePieceEditor = NULL;
}

ImagePieceEditor& ImagePieceEditor::GetInstance()
{
	return *m_pImagePieceEditor;
}

void ImagePieceEditor::SetSelection(const PieceInfo* pPieceInfo)
{
	m_pPieceInfo = pPieceInfo;
	Refresh(false);
}

const PieceInfo* ImagePieceEditor::GetSelection() const
{
	return m_pPieceInfo;
}

bool ImagePieceEditor::SetImage(const ImageInfo* pImageInfo)
{
	if (m_pImageInfo == pImageInfo) return false;
	m_pImageInfo = pImageInfo;

	UpdateVirtualSize();
	UpdateScrollPosition(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
	return true;
}

const ImageInfo* ImagePieceEditor::GetImage() const
{
	return m_pImageInfo;
}

wxSize ImagePieceEditor::CalculateVirtualSize()
{
	if (!m_pImageInfo)	return wxSize(0, 0);

	const wxBitmap* pBitmap = ((ImageInfo*)m_pImageInfo)->GetBitmap();
	if (!pBitmap) return wxSize(0, 0);

	return pBitmap->GetSize();
}

void ImagePieceEditor::Draw(wxDC& dc)
{
	if (!m_pImageInfo) return;

	DrawImage(dc, wxPoint(0, 0), m_pImageInfo);
	DrawSelection(dc);
}

void ImagePieceEditor::DrawSelection(wxDC& dc)
{
	if (!m_pPieceInfo) return;

 	dc.SetPen(*wxRED_PEN);
 	dc.SetBrush(*wxTRANSPARENT_BRUSH);
	DrawRectangle(dc, m_pPieceInfo->GetRect());
}

void ImagePieceEditor::OnLButtonDown(const wxPoint& pos)
{
	wxPoint posMouse = (pos + GetOriginOffset()) / GetZoom();
	const PieceInfo* pPieceInfo = ImagePieceDocument::GetInstance().FindPieceInfoUnderPoint(posMouse, m_pImageInfo);
	SetSelection(pPieceInfo);

	PieceListTransformer::GetInstance().SetSelectedPieceInfo(pPieceInfo);
	PieceListTransformer::GetInstance().UpdateProperty(pPieceInfo);
	if (!pPieceInfo && m_pImageInfo)
	{
		ImageListTransformer::GetInstance().UpdateProperty(m_pImageInfo);
	}
}
