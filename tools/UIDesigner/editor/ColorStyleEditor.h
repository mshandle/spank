/*!
 * \file ColorStyleEditor.h
 * \date 2-15-2012 14:16:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __COLORSTYLEEDITOR_H__
#define __COLORSTYLEEDITOR_H__

#include "BaseEditor.h"
#include "../document/ColorStyle.h"

class ColorStyleEditor : public BaseEditor
{
public:
	enum CONST_DEFINE
	{
		DEFAULT_PIECE_SIZE = 100,
	};

public:
	ColorStyleEditor();
	ColorStyleEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual ~ColorStyleEditor();

	static ColorStyleEditor& GetInstance();

	bool SetColorStyle(ColorStyle* pColorStyle);
	ColorStyle* GetColorStyle();

	virtual wxSize CalculateVirtualSize();
	virtual void Draw(wxDC& dc);
	virtual void OnLButtonDown(const wxPoint& pos);

	void SetSelState(IStyle::STYLE_STATE eState);
	IStyle::STYLE_STATE GetSelState() const;

private:
	void Init();
	void Release();

	void UpdateSubRect();

	void DrawSelection(wxDC& dc);

private:
	static ColorStyleEditor* m_pColorStyleEditor;
	ColorStyle* m_pColorStyle;

	IStyle::STYLE_STATE m_eSelState;
	wxRect m_rectState[IStyle::SS_NUM];
	wxSize m_TotalSize;

};
#endif // __COLORSTYLEEDITOR_H__
