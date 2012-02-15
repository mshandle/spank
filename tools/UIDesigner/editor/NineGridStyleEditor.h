/*!
 * \file NineGridStyleEditor.h
 * \date 2-15-2012 12:44:33
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NINEGRIDSTYLEEDITOR_H__
#define __NINEGRIDSTYLEEDITOR_H__

#include "BaseEditor.h"
#include "../document/NineGridStyle.h"

class NineGridStyleEditor : public BaseEditor
{
public:
	NineGridStyleEditor();
	NineGridStyleEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual ~NineGridStyleEditor();

	static NineGridStyleEditor& GetInstance();

	bool SetNineGridStyle(NineGridStyle* pNineGridStyle);
	NineGridStyle* GetNineGridStyle();

	virtual wxSize CalculateVirtualSize();
	virtual void Draw(wxDC& dc);
	virtual void OnLButtonDown(const wxPoint& pos);

	void SetSelState(IStyle::STYLE_STATE eState);
	IStyle::STYLE_STATE GetSelState() const;

private:
	void Init();
	void Release();

	void UpdateSubBitmap();
	void UpdateSubBitmapRect();

	void DrawSelection(wxDC& dc);

private:
	static NineGridStyleEditor* m_pNineGridStyleEditor;
	NineGridStyle* m_pNineGridStyle;

	IStyle::STYLE_STATE m_eSelState;
	wxBitmap m_bmpState[IStyle::SS_NUM];
	wxRect m_rectState[IStyle::SS_NUM];
	wxSize m_TotalSize;
};
#endif // __NINEGRIDSTYLEEDITOR_H__
