/*!
 * \file CombinaPiece.cpp
 * \date 2011/10/18 10:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "CombinaPiece.h"

bool CombinaPiece::Combina(const UIImagePieceView::TM_PIECE& vPieceMap, const UIImagePieceView::TM_BITMAP_CACHE& vImageMap)
{

	typedef std::map<wxString, wxImage*> TM_SAVAIMAGE;
	TM_SAVAIMAGE SavaImage;
	for(UIImagePieceView::TM_BITMAP_CACHE::const_iterator it = vImageMap.begin(); it != vImageMap.end(); ++it)
	{
		wxImage* pImage = new wxImage(it->second->ConvertToImage());
		SavaImage.insert(std::make_pair(it->first, pImage));
	}
	for (UIImagePieceView::TM_PIECE::const_iterator PieceIt = vPieceMap.begin(); PieceIt != vPieceMap.end(); PieceIt++)
	{
		wxString ImageStr = PieceIt->second.StrBackGroundImage;
		TM_SAVAIMAGE::iterator it = SavaImage.find(ImageStr);
		if(it == SavaImage.end())continue;
		wxImage* Image = it->second;
		wxImage SubImage (PieceIt->second.pBitMap->ConvertToImage());
		Image->Paste(SubImage, PieceIt->second.rect.x, PieceIt->second.rect.y);
	}

	for(TM_SAVAIMAGE::iterator it = SavaImage.begin(); it != SavaImage.end(); ++it)
	{
		it->second->SaveFile(it->first, wxBITMAP_TYPE_PNG);
	}
	return true;
}