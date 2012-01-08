/*!
 * \file PieceCombiner.cpp
 * \date 2011/10/18 10:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#include "PieceCombiner.h"
#include "UIImagePieceView.h"
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <wx/wx.h>
#include <wx/bitmap.h>

bool PieceCombiner::Combine(const UIImagePieceView::TM_PIECE& vPieceMap, const UIImagePieceView::TM_BITMAP_CACHE& vImageMap)
{
	TM_SAVA_IMAGE saveImageMap;
	for(UIImagePieceView::TM_BITMAP_CACHE::const_iterator it = vImageMap.begin(); it != vImageMap.end(); ++it)
	{
		const wxBitmap* pBitmap = (it->second);
		wxImage* pImage = new wxImage(pBitmap->ConvertToImage());
		saveImageMap.insert(std::make_pair(it->first, pImage));
	}

	for (UIImagePieceView::TM_PIECE::const_iterator it = vPieceMap.begin(); it != vPieceMap.end(); ++it)
	{
		const UIImagePieceView::PIECEVIEW_INFO& pieceViewInfo = (it->second);
		wxString strImage = pieceViewInfo.strBgImage;

		TM_SAVA_IMAGE::iterator itSaveImage = saveImageMap.find(strImage);
		if (itSaveImage == saveImageMap.end()) continue;
		wxImage* pImage = (itSaveImage->second);

		wxImage subImage = pieceViewInfo.pBitmap->ConvertToImage();
		pImage->Paste(subImage, pieceViewInfo.rect.x, pieceViewInfo.rect.y);
	}

	for(TM_SAVA_IMAGE::iterator it = saveImageMap.begin(); it != saveImageMap.end(); ++it)
	{
		const wxImage* pImage = (it->second);
		pImage->SaveFile(it->first, wxBITMAP_TYPE_PNG);
	}

	return true;
}

bool PieceCombiner::SortPiece(UIImagePieceDocument::TM_PIECE_INFO& vPieceMap,  UIImagePieceView::TM_BITMAP_CACHE& vImageMap, const UIImagePieceDocument::TM_IMAGE_INFO& ImagfInfo)
{
	//this a bin_packing problem (NP problem)
	
	typedef std::vector<PieceCombiner::PIECE_INFO*> TV_PIECE;
	std::vector<PieceCombiner::IMAGE_INFO> vImageList;
	for(UIImagePieceView::TM_BITMAP_CACHE::const_iterator ImageIt = vImageMap.begin(); ImageIt != vImageMap.end();)
	{	
		TV_PIECE vPieces;
		wxImage* Image = CreatePngTexture(ImageIt->second->GetWidth(), ImageIt->second->GetHeight());
		wxImage BackGround = ImageIt->second->ConvertToImage();
		int nImageID = 0;
		//each the image Id will has a difference vector of pieces;
		for(UIImagePieceDocument::TM_IMAGE_INFO::const_iterator ImageInfoIt = ImagfInfo.begin(); ImageInfoIt != ImagfInfo.end(); ++ImageInfoIt)
		{
			if(ImageInfoIt->second.strFile == ImageIt->first)
			{
				nImageID = ImageInfoIt->second.nId;
				break;
			}
		}
		for(UIImagePieceDocument::TM_PIECE_INFO::iterator PieceIt = vPieceMap.begin(); PieceIt != vPieceMap.end();)
		{
			if(nImageID ==  PieceIt->second.nImageId)
			{
				wxImage* piece = new wxImage(BackGround.GetSubImage(PieceIt->second.pieceRect));
				PieceCombiner::PIECE_INFO* pPieceInfo = new PieceCombiner::PIECE_INFO();
				pPieceInfo->pImagePiece =piece;
				pPieceInfo->strPieceName = PieceIt->second.strId;
				pPieceInfo->nImageId = PieceIt->second.nImageId;
				vPieces.push_back(pPieceInfo);

				PieceIt = vPieceMap.erase(PieceIt);
			}
			else
			{
				++PieceIt;
			}
		}

		//Sort the pieces;
		std::sort(vPieces.begin(),vPieces.end(), Compare);
		int nStartX = 0;
		int ImageWidtht = Image->GetWidth();
		int* flag = new int[ImageWidtht];
		memset(flag, 0, ImageWidtht * sizeof(int));
		//calu the position of every the pieces;
		for(TV_PIECE::iterator PiecesIt = vPieces.begin(); PiecesIt != vPieces.end(); ++PiecesIt)
		{
			int Width = Image->GetWidth();
			if((nStartX +(*PiecesIt)->pImagePiece->GetWidth()) > Width)
			{
				nStartX = 0;
			}
			int nheight = GetMaxHeight(flag, Image->GetWidth(), nStartX, nStartX + (*PiecesIt)->pImagePiece->GetWidth());
			Image->Paste(*(*PiecesIt)->pImagePiece, nStartX, nheight);
			SetMaxHeight(flag, ImageWidtht, nStartX, nStartX + (*PiecesIt)->pImagePiece->GetWidth(), nheight + (*PiecesIt)->pImagePiece->GetHeight());
			(*PiecesIt)->pieceRect.x = nStartX;
			(*PiecesIt)->pieceRect.y = nheight;
			(*PiecesIt)->pieceRect.width = (*PiecesIt)->pImagePiece->GetWidth();
			(*PiecesIt)->pieceRect.height = (*PiecesIt)->pImagePiece->GetHeight();
			nStartX += X_OFF;
			nStartX += (*PiecesIt)->pImagePiece->GetWidth();
		}

		//Update the project of piece information;
		for(TV_PIECE::iterator it = vPieces.begin(); it != vPieces.end();)
		{
			UIImagePieceDocument::PIECE_INFO pieceInfo;
			pieceInfo.nImageId = (*it)->nImageId;
			pieceInfo.pieceRect = (*it)->pieceRect;
			pieceInfo.strId = (*it)->strPieceName;
			delete (*it)->pImagePiece;
			it = vPieces.erase(it);
			vPieceMap.insert(std::make_pair(pieceInfo.strId, pieceInfo));
		}
		wxBitmap* pBitMap = new wxBitmap(*Image,  32);
		IMAGE_INFO imageinfo;
		imageinfo.strImageName = ImageIt->first;
		imageinfo.pBitmap = pBitMap;
		delete ImageIt->second;
		ImageIt = vImageMap.erase(ImageIt);
		vImageList.push_back(imageinfo);
	}
	//update the bitmapcache of UIImagePieceView;
	for(std::vector<IMAGE_INFO>::iterator it = vImageList.begin(); it != vImageList.end(); ++it)
	{
		vImageMap.insert(std::make_pair((*it).strImageName, (*it).pBitmap));
	}
	return true;
}

bool PieceCombiner::Compare(const PIECE_INFO* rvalue, const PIECE_INFO* lvalue )
{
	int rvalueRect = rvalue->pImagePiece->GetHeight() * rvalue->pImagePiece->GetWidth();
	int lvalueRect = lvalue->pImagePiece->GetHeight() * lvalue->pImagePiece->GetWidth();
	return rvalueRect > lvalueRect;
}

wxImage* PieceCombiner::CreatePngTexture(int Width, int Height)
{
	wxImage* Image = new wxImage(Width, Height, false);
	Image->InitAlpha();
	for(int x = 0; x < Image->GetWidth(); ++x)
	{
		for(int y = 0; y < Image->GetHeight(); ++y)
		{
			Image->SetAlpha(x, y, 0);
		}
	}
	return Image;
}

int PieceCombiner::GetMaxHeight(int* flag, int nsize, int nStart, int nEnd)
{
	int value = 0;
	for(int n = nStart; n < nEnd; n++)
	{

		if(flag[n] > value)
		{
			value = flag[n];
		}
	}
	return value;
}

void PieceCombiner::SetMaxHeight(int*& flag, int nsize, int nStart, int nEnd, int value)
{
	for(int n = nStart; n < nEnd; n++)
	{
		flag[n] = value;
	}
}