/*!
 * \file ImageListTransformer.cpp
 * \date 2-14-2012 1:02:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ImageListTransformer.h"
#include "../document/ImagePieceDocument.h"

ImageListTransformer::ImageListTransformer()
{
	m_pListView = NULL;
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

bool ImageListTransformer::Initialize(wxTreeCtrl* pTreeCtrl)
{
	m_pListView = pTreeCtrl;
	return true;
}

void ImageListTransformer::UpdateListView()
{
	m_pListView->DeleteAllItems();
	wxTreeItemId rootItem = m_pListView->AddRoot(wxT("ImageInfo"));

	ImagePieceDocument::TM_IMAGE_INFO& ImageInfoMap = ImagePieceDocument::GetInstance().GetImageInfoMap();
	for (ImagePieceDocument::TM_IMAGE_INFO::iterator it = ImageInfoMap.begin(); it != ImageInfoMap.end(); ++it)
	{
		ImageInfo* pImageInfo = it->second;
		wxTreeItemId itemId = m_pListView->AppendItem(rootItem, pImageInfo->GetId());
		pImageInfo->SetTreeItemId(itemId);
	}
	m_pListView->ExpandAll();
}

ImageInfo* ImageListTransformer::GetSelectedImageInfo()
{
	wxString strImageId = m_pListView->GetItemText(m_pListView->GetSelection());
	ImageInfo* pImageInfo = ImagePieceDocument::GetInstance().FindImageInfo(strImageId);
	return pImageInfo;
}

void ImageListTransformer::SetSelectedItem(ImageInfo* pImageInfo)
{
	if (pImageInfo)
	{
		m_pListView->SelectItem(pImageInfo->GetTreeItemId(), true);
	}
}