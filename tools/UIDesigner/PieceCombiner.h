/*!
 * \file PieceCombiner.h
 * \date 2011/10/18 10:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gami.com)
 */
#ifndef __PIECECOMBINER_H__
#define __PIECECOMBINER_H__

#include <wx/wx.h>
#include <wx/file.h>
#include <map>

#include "UIImagePieceView.h"
#include "UIImagePieceDocument.h"

class PieceCombiner 
{
public:
	enum CONST_DEFINE
	{
		X_OFF = 2,
		Y_OFF = 2
	};

	typedef struct PIECE_INFO_tag
	{
		wxImage* pImagePiece;
		int nImageId;
		wxString strPieceName;
		wxRect pieceRect;
	} PIECE_INFO;

	typedef struct IMAGE_INFO_tag
	{
		wxString strImageName;
		wxBitmap* pBitmap;
	} IMAGE_INFO;

	typedef std::map<wxString, wxImage*> TM_SAVA_IMAGE;

public:
	static bool Combine(const UIImagePieceView::TM_PIECE& vPieceMap, const UIImagePieceView::TM_BITMAP_CACHE& vImageMap);
	static bool SortPiece(UIImagePieceDocument::TM_PIECE_INFO& vPieceMap, UIImagePieceView::TM_BITMAP_CACHE& vImageMap, const UIImagePieceDocument::TM_IMAGE_INFO& ImagfInfo);

	static int GetMaxHeight(int* flag, int nSize, int nStart, int nEnd);
	static void SetMaxHeight(int*& flag, int nSize, int nStart, int nEnd, int value);

	static bool Compare(const PIECE_INFO* rvalue, const PIECE_INFO* lvalue);

private:
	static wxImage* CreatePngTexture(int Width, int Height);

};
#endif // __PIECECOMBINER_H__
