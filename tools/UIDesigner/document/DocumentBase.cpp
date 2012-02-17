/*!
 * \file DocumentBase.cpp
 * \date 2-14-2012 1:22:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DocumentBase.h"
#include "../DesignerFrame.h"

DocumentBase::DocumentBase()
{
	m_bModifiedFlag = false;
}

DocumentBase::~DocumentBase()
{
}

void DocumentBase::SetFilePath(const wxString& strFilePath)
{
	m_strFilePath = strFilePath;
}

const wxString& DocumentBase::GetFilePath() const
{
	return m_strFilePath;
}

void DocumentBase::SetModifiedFlag()
{
	m_bModifiedFlag = true;
	DesignerFrame::GetInstance().UpdateTitle(m_bModifiedFlag);
}

void DocumentBase::ClearModifiedFlag()
{
	m_bModifiedFlag = false;
}

bool DocumentBase::isModified() const
{
	return m_bModifiedFlag;
}
