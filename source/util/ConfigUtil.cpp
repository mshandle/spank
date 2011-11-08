/*!
 * \file ConfigUtil.cpp
 * \date 7-25-2011 10:11:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <util/ConfigUtil.h>

ConfigUtil& ConfigUtil::GetInstance()
{
	static ConfigUtil s_ConfigUtil;
	return s_ConfigUtil;
}

ConfigUtil::ConfigUtil()
{
	// TODO: 
}

ConfigUtil::~ConfigUtil()
{
	// TODO: 
}

bool ConfigUtil::Initialize()
{
	return true;
}

void ConfigUtil::Terminate()
{
	m_mapString.clear();
	m_mapInt.clear();
	m_mapPointer.clear();
}

void ConfigUtil::AddString(const char* pszKey, const char* pszValue)
{
	std::string strKey = pszKey;
	std::string strValue = pszValue;
	m_mapString.insert(std::make_pair(strKey, strValue));
}

const char* ConfigUtil::GetString(const char* pszKey, const char* pszDefaultValue /*= NULL*/)
{
	std::string strKey = pszKey;
	TM_STRING::iterator itfound = m_mapString.find(strKey);
	if (itfound == m_mapString.end()) return pszDefaultValue;

	return itfound->second.c_str();
}

void ConfigUtil::AddInt(const char* pszKey, int nValue)
{
	std::string strKey = pszKey;
	m_mapInt.insert(std::make_pair(strKey, nValue));
}

int ConfigUtil::GetInt(const char* pszKey, int nDefaultValue /* = 0 */)
{
	std::string strKey = pszKey;
	TM_INT::iterator itfound = m_mapInt.find(strKey);
	if (itfound == m_mapInt.end()) return nDefaultValue;

	return itfound->second;
}

void ConfigUtil::AddPointer(const char* pszKey, void* pValue)
{
	std::string strKey = pszKey;
	m_mapPointer.insert(std::make_pair(strKey, pValue));
}

void* ConfigUtil::GetPointer(const char* pszKey, void* pDefaultValue /*= NULL*/)
{
	std::string strKey = pszKey;
	TM_POINTER::iterator itfound = m_mapPointer.find(strKey);
	if (itfound == m_mapPointer.end()) return pDefaultValue;

	return itfound->second;
}
