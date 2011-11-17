/*!
 * \file PokerMsgGen.h
 * \date 11-17-2011 14:06:04
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __POKERMSGGEN_H__
#define __POKERMSGGEN_H__

#include "IMsgGen.h"
#include <string>
#include <vector>
#include <map>

class PokerMsgGen : public IMsgGen
{
public:
	typedef struct PROPERTY_INFO_tag
	{
		const char* pszName;
		const char* pszType;
		int nTypeSizeInByte;
		int nArraySize;
	} PROPERTY_INFO;
	typedef std::vector<PROPERTY_INFO> TV_PROPERTY_INFO;

	typedef struct MSG_INFO_tag
	{
		const char* pszClassName;
		const char* pszMsgId;
		int nTotalDataSize;
		TV_PROPERTY_INFO vPropertys;
	} MSG_INFO;

	typedef std::map<std::string, int> TM_STRING_INT_MAP;

public:
	PokerMsgGen();
	virtual ~PokerMsgGen();

	virtual bool CanPause(const char* pszTag);
	virtual bool Parse(TiXmlElement* pElmRoot, const char* pszOutDir);

private:
	int GetTypeSize(const char* pszType);
	bool ParseXmlMessage(MSG_INFO& infoOut, TiXmlElement* pElmMessage);
	bool GenerateClass(const MSG_INFO& info, const char* pszDir);
	bool GenerateH(const MSG_INFO& info, const char* pszDir);
	bool GenerateCPP(const MSG_INFO& info, const char* pszDir);

	bool GenPropertysDeclare(std::string& strInOut, const MSG_INFO& info);
	bool GenPropertysImplementUnpack(std::string& strInOut, const MSG_INFO& info);
	bool GenPropertysImplementPack(std::string& strInOut, const MSG_INFO& info);

	void StringReplace(std::string& strInOut, const char* pszFind, const char* pszReplace);

private:
	TM_STRING_INT_MAP m_TypeSizeMap;

};
#endif // __POKERMSGGEN_H__
