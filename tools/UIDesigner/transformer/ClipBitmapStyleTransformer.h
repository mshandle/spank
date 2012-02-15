/*!
 * \file ClipBitmapStyleTransformer.h
 * \date 2-14-2012 17:04:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CLIPBITMAPSTYLETRANSFORMER_H__
#define __CLIPBITMAPSTYLETRANSFORMER_H__

#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include "../document/ClipBitmapStyle.h"

class ClipBitmapStyleTransformer
{
public:
	static ClipBitmapStyleTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid);
	void UpdateListView();
	void UpdateProperty(ClipBitmapStyle* pClipBitmapStyle);
	void PropertyChanged(wxPGProperty* pProperty);

	void SetSelectedClipBitmapStyle(ClipBitmapStyle* pClipBitmapStyle);
	ClipBitmapStyle* GetSelectedClipBitmapStyle();

protected:
	ClipBitmapStyleTransformer();
	~ClipBitmapStyleTransformer();

private:
	wxTreeCtrl* m_pListView;
	wxPropertyGrid* m_pPropertyGrid;

};
#endif // __CLIPBITMAPSTYLETRANSFORMER_H__
