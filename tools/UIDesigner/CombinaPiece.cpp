/*!
 * \file CombinaPiece.cpp
 * \date 2011/10/18 10:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#include "CombinaPiece.h"
#include "UIImagePieceView.h"
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <wx/wx.h>
#include <wx/bitmap.h>

#define  X_OFF  2;
#define  Y_OFF  2;

bool CombinaPiece::Combina(const UIImagePieceView::TM_PIECE& vPieceMap, const UIImagePieceView::TM_BITMAP_CACHE& vImageMap)
{

	typedef std::map<wxString, wxImage*> TM_SAVAIMAGE;
	TM_SAVAIMAGE SavaImage;
	for(UIImagePieceView::TM_BITMAP_CACHE::const_iterator it = vImageMap.begin(); it != vImageMap.end(); ++it)
	{
		wxImage* pImage = new wxImage(it->second->ConvertToImage());
		SavaImage.insert(std::make_pair(it->first, pImage));
	}
	for (UIImagePieceView::TM_PIECE::const_iterator PieceIt = vPieceMap.begin(); PieceIt != vPieceMap.end(); ++PieceIt)
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

bool CombinaPiece::SortPiece(UIImagePieceDocument::TM_PIECE_INFO& vPieceMap,  UIImagePieceView::TM_BITMAP_CACHE& vImageMap, const UIImagePieceDocument::TM_IMAGE_INFO& ImagfInfo)
{
	//this a bin_packing problem (NP problem)
	
	typedef std::vector<CombinaPiece::MyPiece*> TV_PIECE;
	std::vector<CombinaPiece::MyImage> vImageList;
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
				nImageID = ImageInfoIt->second.nID;
				break;
			}
		}
		for(UIImagePieceDocument::TM_PIECE_INFO::iterator PieceIt = vPieceMap.begin(); PieceIt != vPieceMap.end();)
		{
			if(nImageID ==  PieceIt->second.nImageID)
			{
				wxImage* piece = new wxImage(BackGround.GetSubImage(PieceIt->second.rect));
				CombinaPiece::MyPiece* PMypiece = new CombinaPiece::MyPiece();
				PMypiece->Piece =piece;
				PMypiece->PieceName = PieceIt->second.strID;
				PMypiece->ImageID = PieceIt->second.nImageID;
				vPieces.push_back(PMypiece);

				PieceIt = vPieceMap.erase(PieceIt);
			}
			else
			{
				++PieceIt;
			}
		}

		//Sort the pieces;
		std::sort(vPieces.begin(),vPieces.end(), compare);
		int nStartX = 0;
		int ImageWidtht = Image->GetWidth();
		int* flag = new int[ImageWidtht];
		memset(flag, 0, ImageWidtht * sizeof(int));
		//calu the position of every the pieces;
		for(TV_PIECE::iterator PiecesIt = vPieces.begin(); PiecesIt != vPieces.end(); ++PiecesIt)
		{
			int Width = Image->GetWidth();
			if((nStartX +(*PiecesIt)->Piece->GetWidth()) > Width)
			{
				nStartX = 0;
			}
			int nheight = GetMaxHeight(flag, Image->GetWidth(), nStartX, nStartX + (*PiecesIt)->Piece->GetWidth());
			Image->Paste(*(*PiecesIt)->Piece, nStartX, nheight);
			SetMaxHeight(flag, ImageWidtht, nStartX, nStartX + (*PiecesIt)->Piece->GetWidth(), nheight + (*PiecesIt)->Piece->GetHeight());
			(*PiecesIt)->rect.x = nStartX;
			(*PiecesIt)->rect.y = nheight;
			(*PiecesIt)->rect.width = (*PiecesIt)->Piece->GetWidth();
			(*PiecesIt)->rect.height = (*PiecesIt)->Piece->GetHeight();
			nStartX += X_OFF;
			nStartX += (*PiecesIt)->Piece->GetWidth();
		}

		//Update the project of piece information;
		for(TV_PIECE::iterator it = vPieces.begin(); it != vPieces.end();)
		{
			UIImagePieceDocument::PIECE_INFO pieceInfo;
			pieceInfo.nImageID = (*it)->ImageID;
			pieceInfo.rect = (*it)->rect;
			pieceInfo.strID = (*it)->PieceName;
			delete (*it)->Piece;
			it = vPieces.erase(it);
			vPieceMap.insert(std::make_pair(pieceInfo.strID, pieceInfo));
		}
		wxBitmap* pBitMap = new wxBitmap(*Image,  32);
		MyImage imageinfo;
		imageinfo.ImageName = ImageIt->first;
		imageinfo.bitmap = pBitMap;
		delete ImageIt->second;
		ImageIt = vImageMap.erase(ImageIt);
		vImageList.push_back(imageinfo);
	}
	//update the bitmapcache of UIImagePieceView;
	for(std::vector<MyImage>::iterator it = vImageList.begin(); it != vImageList.end(); ++it)
	{
		vImageMap.insert(std::make_pair((*it).ImageName, (*it).bitmap));
	}
	return true;
}

bool CombinaPiece::compare(const MyPiece* rvalue, const MyPiece* lvalue )
{
	int rvalueRect = rvalue->Piece->GetHeight() * rvalue->Piece->GetWidth();
	int lvalueRect = lvalue->Piece->GetHeight() * lvalue->Piece->GetWidth();
	return rvalueRect > lvalueRect;
}

wxImage* CombinaPiece::CreatePngTexture(int Width, int Height)
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

int CombinaPiece::GetMaxHeight(int* flag, int nsize, int nStart, int nEnd)
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

void CombinaPiece::SetMaxHeight(int*& flag, int nsize, int nStart, int nEnd, int value)
{
	for(int n = nStart; n < nEnd; n++)
	{
		flag[n] = value;
	}
}