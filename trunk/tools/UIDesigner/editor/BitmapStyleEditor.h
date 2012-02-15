/*!
 * \file BitmapStyleEditor.h
 * \date 2-15-2012 11:01:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BITMAPSTYLEEDITOR_H__
#define __BITMAPSTYLEEDITOR_H__

#include "BaseEditor.h"
#include "../document/BitmapStyle.h"

class BitmapStyleEditor : public BaseEditor
{
public:
	BitmapStyleEditor();
	BitmapStyleEditor(wxWindow *parent,
		wxWindowID winid,
		const wxPoint& pos = wxDefaultPosition,
		const wxSize& size = wxDefaultSize,
		long style = 0,
		const wxString& name = wxPanelNameStr);

	virtual ~BitmapStyleEditor();

	static BitmapStyleEditor& GetInstance();

	bool SetBitmapStyle(BitmapStyle* pBitmapStyle);
	BitmapStyle* GetBitmapStyle();

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
	static BitmapStyleEditor* m_pBitmapStyleEditor;
	BitmapStyle* m_pBitmapStyle;

	IStyle::STYLE_STATE m_eSelState;
	wxBitmap m_bmpState[IStyle::SS_NUM];
	wxRect m_rectState[IStyle::SS_NUM];
	wxSize m_TotalSize;

};
#endif // __BITMAPSTYLEEDITOR_H__