/*!
 * \file CombinaPiece.h
 * \date 2011/10/18 10:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gami.com)
 */
#ifndef __COMBINAPIECE_H__
#define __COMBINAPIECE_H__

#include <wx/wx.h>
#include <wx/file.h>
#include <map>

#include "UIImagePieceView.h"
#include "UIImagePieceDocument.h"
class CombinaPiece 
{
public:
	struct MyPiece
	{
		wxImage* Piece;
		int ImageID;
		wxString PieceName;
		wxRect rect;
	};
	struct MyImage
	{
		wxString ImageName;
		wxBitmap* bitmap;
	};
public:
	static bool Combina(const UIImagePieceView::TM_PIECE& vPieceMap, const UIImagePieceView::TM_BITMAP_CACHE& vImageMap);
	static bool SortPiece(UIImagePieceDocument::TM_PIECE_INFO& vPieceMap, UIImagePieceView::TM_BITMAP_CACHE&  vImageMap, const UIImagePieceDocument::TM_IMAGE_INFO& ImagfInfo);

	static int  GetMaxHeight(int* flag, int nsize, int nStart, int nEnd);
	static void SetMaxHeight(int*& flag, int nsize, int nStart, int nEnd, int value);

	static bool compare(const MyPiece* rvalue, const MyPiece* lvalue);
private:
	static wxImage* CreatePngTexture(int Width, int Height);
};

#endif // __COMBINAPIECE_H__