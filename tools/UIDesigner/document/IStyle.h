/*!
 * \file IStyle.h
 * \date 2-14-2012 13:59:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISTYLE_H__
#define __ISTYLE_H__

#include <wx/wx.h>
#include <wx/treectrl.h>

class IStyle
{
public:
	enum STYLE_STATE
	{
		SS_NORMAL = 0,
		SS_DOWN,
		SS_HOVER,
		SS_DISABLED,
		SS_NUM
	};

public:
	IStyle();
	~IStyle();

	const wxString& GetId() const;

	void SetTreeItemId(wxTreeItemId itemId);
	wxTreeItemId GetTreeItemId();

protected:
	void SetId(const wxString& strId);

private:
	wxString m_strId;
	wxTreeItemId m_TreeItemId;

};

#endif // __ISTYLE_H__
