/*!
 * \file ClipBitmapStyle.h
 * \date 2-14-2012 16:43:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CLIPBITMAPSTYLE_H__
#define __CLIPBITMAPSTYLE_H__

#include "IStyle.h"
#include "PieceInfo.h"
#include <tinyxml-2.6.2/tinyxml.h>

class ClipBitmapStyle : public IStyle
{
public:
	ClipBitmapStyle();
	~ClipBitmapStyle();

	bool LoadFromXml(TiXmlElement* pElmClipBitmapStyle);
	bool SaveToXml(TiXmlElement* pElmClipBitmapStyleList);

	bool SetStatePiece(PieceInfo* pPieceInfo, STYLE_STATE eState);
	PieceInfo* GetStatePiece(STYLE_STATE eState);

private:
	PieceInfo* LoadStateInfo(TiXmlElement* pElmClipBitmapStyle, const wxString& strState, PieceInfo* pDefaultPieceInfo);
	bool SaveStateInfo(TiXmlElement* pElmClipBitmapStyle, const wxString& strState, PieceInfo* pPieceInfo, bool force = false);

private:
	PieceInfo* m_PieceInfo[SS_NUM];

};
#endif // __CLIPBITMAPSTYLE_H__
