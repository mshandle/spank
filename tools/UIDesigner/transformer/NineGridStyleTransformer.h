/*!
 * \file NineGridStyleTransformer.h
 * \date 2-14-2012 16:08:10
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NINEGRIDSTYLETRANSFORMER_H__
#define __NINEGRIDSTYLETRANSFORMER_H__

#include <wx/treectrl.h>
#include "../document/NineGridStyle.h"

class NineGridStyleTransformer
{
public:
	static NineGridStyleTransformer& GetInstance();

	bool Initialize(wxTreeCtrl* pTreeCtrl);
	void UpdateListView();

	NineGridStyle* GetSelectedNineGridStyle();
	void SetSelectedNineGridStyle(NineGridStyle* pNineGrieStyle);

protected:
	NineGridStyleTransformer();
	~NineGridStyleTransformer();

private:
	wxTreeCtrl* m_pListView;

};
#endif // __NINEGRIDSTYLETRANSFORMER_H__
