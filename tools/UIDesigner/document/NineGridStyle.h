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

	NINE_GRID_INFO* GetStateGridInfo(STYLE_STATE eState);

private:
	NINE_GRID_INFO* LoadStateInfo(TiXmlElement* pElmNineGridStyle, const wxString& strState, NINE_GRID_INFO* pDefaultInfo);
	bool SaveStateInfo(TiXmlElement* pElmNineGridStyle, const wxString& strState, NINE_GRID_INFO* pNineGridInfo, bool force = false);
	void Clear();

private:
	NINE_GRID_INFO* m_NineGridInfo[SS_NUM];

};
#endif // __NINEGRIDSTYLE_H__
