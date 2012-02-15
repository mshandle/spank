/*!
 * \file NineGridStyle.h
 * \date 2-14-2012 15:07:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NINEGRIDSTYLE_H__
#define __NINEGRIDSTYLE_H__

#include "IStyle.h"
#include "PieceInfo.h"
#include <tinyxml-2.6.2/tinyxml.h>

class NineGridStyle : public IStyle
{
public:
	typedef struct NINE_GRID_INFO_tag
	{
		PieceInfo* pPieceInfo;
		int min_x;
		int min_y;
		int max_x;
		int max_y;
	} NINE_GRID_INFO;

public:
	NineGridStyle();
	~NineGridStyle();

	bool LoadFromXml(TiXmlElement* pElmNineGridStyle);
	bool SaveToXml(TiXmlElement* pElmNineGridStyleList);

	bool SetStatePiece(PieceInfo* pPieceInfo, STYLE_STATE eState);
	bool SetStateMinX(int value, IStyle::STYLE_STATE eState);
	bool SetStateMinY(int value, IStyle::STYLE_STATE eState);
	bool SetStateMaxX(int value, IStyle::STYLE_STATE eState);
	bool SetStateMaxY(int value, IStyle::STYLE_STATE eState);

	NINE_GRID_INFO* GetStateGridInfo(STYLE_STATE eState);

private:
	bool LoadStateInfo(NINE_GRID_INFO& NineGridInfoOut, TiXmlElement* pElmNineGridStyle, const wxString& strState);
	bool SaveStateInfo(TiXmlElement* pElmNineGridStyle, const wxString& strState, const NINE_GRID_INFO& NineGridInfo, bool force = false);
	bool IsNormalGrid(const NINE_GRID_INFO& NineGridInfo);

private:
	NINE_GRID_INFO m_NineGridInfo[SS_NUM];

};
#endif // __NINEGRIDSTYLE_H__
