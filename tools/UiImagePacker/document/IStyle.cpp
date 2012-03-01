/*!
 * \file IStyle.cpp
 * \date 2-14-2012 13:59:16
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "IStyle.h"

IStyle::IStyle()
{
	// TODO: 
}

IStyle::~IStyle()
{
	// TODO: 
}

void IStyle::SetId(const wxString& strId)
{
	m_strId = strId;
}

const wxString& IStyle::GetId() const
{
	return m_strId;
}

void IStyle::SetTreeItemId(wxTreeItemId itemId)
{
	m_TreeItemId = itemId;
}

const wxTreeItemId& IStyle::GetTreeItemId() const
{
	return m_TreeItemId;
}

wxXmlNode* IStyle::FindXmlChild(wxXmlNode* pParent, const wxString& name)
{
	wxXmlNode* pChild = pParent->GetChildren();
	while (pChild)
	{
		if (pChild->GetName() == name) return pChild;
		pChild = pChild->GetNext();
	}

	return NULL;
}
