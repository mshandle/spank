/*!
 * \file ImageListTransformer.cpp
 * \date 2-14-2012 1:02:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImageListTransformer.h"
#include "../DesignerFrame.h"
#include "../document/ImagePieceDocument.h"

ImageListTransformer::ImageListTransformer()
{
	m_pListView = NULL;
	m_pPropertyGrid = NULL;
}

ImageListTransformer::~ImageListTransformer()
{
	// TODO: 
}

ImageListTransformer& ImageListTransformer::GetInstance()
{
	static ImageListTransformer s_ImageListTransformer;
	return s_ImageListTransformer;
}

bool ImageListTransformer::Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid)
{
	m_pListView = pTreeCtrl;
	m_pPropertyGrid = pPropertyGrid;
	return true;
}

void ImageListTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("ImageList"));

	ImagePieceDocument::TM_IMAGE_INFO& ImageInfoMap = ImagePieceDocument::GetInstance().GetImageInfoMap();
	for (ImagePieceDocument::TM_IMAGE_INFO::iterator it = ImageInfoMap.begin(); it != ImageInfoMap.end(); ++it)
	{
		ImageInfo* pImageInfo = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pImageInfo->GetId());
		pImageInfo->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

void ImageListTransformer::UpdateProperty(ImageInfo* pImageInfo)
{
	m_pPropertyGrid->Clear();
	DesignerFrame::GetInstance().SetCurrPropertyType(DesignerFrame::PT_UNKNOWN);
	if (!pImageInfo) return;

	m_pPropertyGrid->Append(new wxStringProperty("id", "id", pImageInfo->GetId()));
	m_pPropertyGrid->Append(new wxFileProperty("path", "path", pImageInfo->GetPath()))->Enable(false);
	DesignerFrame::GetInstance().SetCurrPropertyType(DesignerFrame::PT_IMAGE);
}

void ImageListTransformer::PropertyChanged(wxPGProperty* pProperty)
{
	ImageInfo* pImageInfo = GetSelectedImageInfo();
	if (!pImageInfo) return;

	if (pProperty->GetName() == "id")
	{
		wxString strNewId = pProperty->GetValueAsString();
		ImagePieceDocument::GetInstance().RenameImageInfoId(pImageInfo, strNewId);
	}
}

void ImageListTransformer::SetSelectedImageInfo(ImageInfo* pImageInfo)
{
	if (!pImageInfo) return;

	m_pListView->SelectItem(pImageInfo->GetTreeItemId(), true);
}

ImageInfo* ImageListTransformer::GetSelectedImageInfo()
{
	wxString strImageId = m_pListView->GetItemText(m_pListView->GetSelection());
	ImageInfo* pImageInfo = ImagePieceDocument::GetInstance().FindImageInfo(strImageId);
	return pImageInfo;
}
