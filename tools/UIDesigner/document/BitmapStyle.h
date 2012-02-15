/*!
 * \file BitmapStyle.h
 * \date 2-14-2012 13:52:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BITMAPSTYLE_H__
#define __BITMAPSTYLE_H__

#include "IStyle.h"
#include "PieceInfo.h"
#include <tinyxml-2.6.2/tinyxml.h>

class BitmapStyle : public IStyle
{
public:
	BitmapStyle();
	~BitmapStyle();

	bool LoadFromXml(TiXmlElement* pElmBitmapStyle);
	bool SaveToXml(TiXmlElement* pElmBitmapStyleList);

	bool SetStatePiece(PieceInfo* pPieceInfo, STYLE_STATE eState);
	PieceInfo* GetStatePiece(STYLE_STATE eState);

private:
	PieceInfo* LoadStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, PieceInfo* defaultPieceInfo);
	bool SaveStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, PieceInfo* pPieceInfo, bool force = false);

private:
	PieceInfo* m_PieceInfo[SS_NUM];

};
#endif // __BITMAPSTYLE_H__
