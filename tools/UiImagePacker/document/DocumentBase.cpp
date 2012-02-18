/*!
 * \file DocumentBase.cpp
 * \date 2-14-2012 1:22:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DocumentBase.h"
#include "../ImagePackerFrame.h"

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
	ImagePackerFrame::GetInstance().UpdateUiModified(m_bModifiedFlag);
}

void DocumentBase::ClearModifiedFlag()
{
	m_bModifiedFlag = false;
}

bool DocumentBase::IsModified() const
{
	return m_bModifiedFlag;
}
