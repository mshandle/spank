/*!
 * \file IObject.cpp
 * \date 8-16-2011 11:16:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IObject.h>

IObject::IObject()
{
	m_bOK = false;
	m_nRef = 1;
	m_pParent = NULL;
}

IObject::IObject(IObject* pParent)
{
	m_bOK = false;
	m_nRef = 1;
	m_pParent = pParent;
}

IObject::~IObject()
{
	// TODO: 
}

bool IObject::IsOK() const
{
	return m_bOK;
}

void IObject::Release()
{
	if (DecRef() <= 0)
	{
		delete this;
	}
}

IObject* IObject::GetParent() const
{
	return m_pParent;
}

void IObject::SetParent(IObject* pParent)
{
	m_pParent = pParent;
}

int IObject::IncRef()
{
	return ++m_nRef;
}

int IObject::DecRef()
{
	return --m_nRef;
}

int IObject::GetRef() const
{
	return m_nRef;
}

void IObject::SetRef(int ref)
{
	m_nRef = ref;
}
