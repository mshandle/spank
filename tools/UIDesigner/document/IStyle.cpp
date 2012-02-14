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

const wxString& IStyle::GetId() const
{
	return m_strId;
}

void IStyle::SetId(const wxString& strId)
{
	m_strId = strId;
}

void IStyle::SetTreeItemId(wxTreeItemId itemId)
{
	m_TreeItemId = itemId;
}

wxTreeItemId IStyle::GetTreeItemId()
{
	return m_TreeItemId;
}
