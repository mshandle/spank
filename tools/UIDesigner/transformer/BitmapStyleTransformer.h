/*!
 * \file BitmapStyleTransformer.h
 * \date 2-14-2012 14:46:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BITMAPSTYLETRANSFORMER_H__
#define __BITMAPSTYLETRANSFORMER_H__

#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include "../document/BitmapStyle.h"

class BitmapStyleTransformer
{
public:
	static BitmapStyleTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid);
	void UpdateListView();
	void UpdateProperty(BitmapStyle* pBitmapStyle);
	void PropertyChanged(wxPGProperty* pProperty);

	void SetSelectedBitmapStyle(BitmapStyle* pBitmapStyle);
	BitmapStyle* GetSelectedBitmapStyle();

protected:
	BitmapStyleTransformer();
	~BitmapStyleTransformer();

private:
	wxTreeCtrl* m_pListView;
	wxPropertyGrid* m_pPropertyGrid;

};
#endif // __BITMAPSTYLETRANSFORMER_H__
