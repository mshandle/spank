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
#include "../document/ClipBitmapStyle.h"

class ClipBitmapStyleTransformer
{
public:
	static ClipBitmapStyleTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl);
	void UpdateListView();

	ClipBitmapStyle* GetSelectedBitmapStyle();
	void SetSelectedBitmapStyle(ClipBitmapStyle* pClipBitmapStyle);

protected:
	ClipBitmapStyleTransformer();
	~ClipBitmapStyleTransformer();

private:
	wxTreeCtrl* m_pListView;

};
#endif // __CLIPBITMAPSTYLETRANSFORMER_H__
