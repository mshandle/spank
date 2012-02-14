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
#include "../document/BitmapStyle.h"

class BitmapStyleTransformer
{
public:
	static BitmapStyleTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl);
	void UpdateListView();

	BitmapStyle* GetSelectedBitmapStyle();
	void SetSelectedBitmapStyle(BitmapStyle* pBitmapStyle);

protected:
	BitmapStyleTransformer();
	~BitmapStyleTransformer();

private:
	wxTreeCtrl* m_pListView;

};
#endif // __BITMAPSTYLETRANSFORMER_H__
