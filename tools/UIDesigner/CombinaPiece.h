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

class CombinaPiece 
{
public:
	static bool Combina(const UIImagePieceView::TM_PIECE& vPieceMap, const UIImagePieceView::TM_BITMAP_CACHE& vImageMap);
};

#endif // __COMBINAPIECE_H__