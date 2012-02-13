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
#include "ImageInfo.h"

class ImageListTransformer
{
public:
	static ImageListTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl);
	void UpdateListView();

	ImageInfo* GetSelectedImageInfo();
	void SetSelectedItem(ImageInfo* pImageInfo);

protected:
	ImageListTransformer();
	~ImageListTransformer();

private:
	wxTreeCtrl* m_pListView;

};
#endif // __IMAGELISTTRANSFORMER_H__
