/*!
 * \file ImageListTransformer.h
 * \date 2-14-2012 1:02:33
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMAGELISTTRANSFORMER_H__
#define __IMAGELISTTRANSFORMER_H__

#include <wx/treectrl.h>
#include <wx/propgrid/propgrid.h>
#include "../document/ImageInfo.h"

class ImageListTransformer
{
public:
	static ImageListTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl, wxPropertyGrid* pPropertyGrid);
	void UpdateListView();
	void UpdateProperty(ImageInfo* pImageInfo);

	void SetSelectedImageInfo(ImageInfo* pImageInfo);
	ImageInfo* GetSelectedImageInfo();

protected:
	ImageListTransformer();
	~ImageListTransformer();

private:
	wxTreeCtrl* m_pListView;
	wxPropertyGrid* m_pPropertyGrid;

};
#endif // __IMAGELISTTRANSFORMER_H__
