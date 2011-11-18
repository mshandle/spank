/*!
 * \file UIString.h
 * \date 8-22-2011 15:43:33
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UISTRING_H__
#define __UISTRING_H__

#include "IFont.h"
#include "UIRect.h"
#include "../math/IMath.h"
#include <vector>

class UIString : public IObject
{
public:
	typedef std::vector<ushort> TV_UNICODE_CHAR;
	typedef std::vector<const CHAR_INFO*> TV_CHAR_INFO;

public:
	DECLARE_RTTI(UIString, IObject);

	UIString(IFont* pFont, const char* pszText);
	UIString(const char* pszText);
	virtual ~UIString();

	void Update(float dt);
	void Render(const Vector2& pos, const Vector2& clipRectPos, const Vector2& clipRectSize);

	bool SetText(const char* pszText);
	const Vector2& GetSize() const;

private:
	bool CreateCharVerts(const char* pszText);
	void ClearCharVerts();

	void RecalculateSize();

private:
	IFont* m_pFont;
	TV_UNICODE_CHAR m_UnicodeChars;
	int m_nCharCount;

	TV_CHAR_INFO m_vCharInfo;
	Vector2 m_vSize;

};
#endif // __UISTRING_H__
