/*!
 * \file DocumentBase.cpp
 * \date 2-14-2012 1:22:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DocumentBase.h"

DocumentBase::DocumentBase()
{
	m_bModifiedFlag = false;
}

DocumentBase::~DocumentBase()
{
}

void DocumentBase::SetModifiedFlag()
{
	m_bModifiedFlag = true;
}

void DocumentBase::ClearModifiedFlag()
{
	m_bModifiedFlag = false;
}

bool DocumentBase::isModified() const
{
	return m_bModifiedFlag;
}
