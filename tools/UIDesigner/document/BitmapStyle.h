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

	bool SetStatePiece(const PieceInfo* pPieceInfo, STYLE_STATE eState);
	const PieceInfo* GetStatePiece(STYLE_STATE eState) const;

private:
	const PieceInfo* LoadStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, const PieceInfo* pDefaultPieceInfo);
	bool SaveStateInfo(TiXmlElement* pElmBitmapStyle, const wxString& strState, const PieceInfo* pPieceInfo, bool force = false);

private:
	const PieceInfo* m_PieceInfo[SS_NUM];

};
#endif // __BITMAPSTYLE_H__
