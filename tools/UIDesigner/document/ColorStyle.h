/*!
 * \file ColorStyle.h
 * \date 2-14-2012 16:21:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __COLORSTYLE_H__
#define __COLORSTYLE_H__

#include "IStyle.h"
#include <tinyxml-2.6.2/tinyxml.h>

class ColorStyle : public IStyle
{
public:
	enum CONST_DEFINE
	{
		DEFAULT_COLOR = 0x808080,
	};

public:
	ColorStyle();
	~ColorStyle();

	bool LoadFromXml(TiXmlElement* pElmColorStyle);
	bool SaveToXml(TiXmlElement* pElmColorStyleList);

	bool SetStateColor(unsigned int color, STYLE_STATE eState);
	unsigned int GetStateColor(STYLE_STATE eState) const;

private:
	unsigned int LoadStateInfo(TiXmlElement* pElmColorStyle, const wxString& strState, unsigned int nDefaultColor);
	bool SaveStateInfo(TiXmlElement* pElmColorStyle, const wxString& strState, unsigned int nColor, bool force = false);

private:
	unsigned int m_nColors[SS_NUM];

};
#endif // __COLORSTYLE_H__
