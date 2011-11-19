/*!
 * \file PokerMsgGen.cpp
 * \date 11-17-2011 14:06:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "PokerMsgGen.h"
#include <iostream>
#include <algorithm>

PokerMsgGen::PokerMsgGen()
{
	m_TypeSizeMap.insert(std::make_pair("bool", 1));
	m_TypeSizeMap.insert(std::make_pair("char", 1));
	m_TypeSizeMap.insert(std::make_pair("uchar", 1));
	m_TypeSizeMap.insert(std::make_pair("short", 2));
	m_TypeSizeMap.insert(std::make_pair("ushort", 2));
	m_TypeSizeMap.insert(std::make_pair("int", 4));
	m_TypeSizeMap.insert(std::make_pair("uint", 4));
	m_TypeSizeMap.insert(std::make_pair("int64", 8));
	m_TypeSizeMap.insert(std::make_pair("uint64", 8));
	m_TypeSizeMap.insert(std::make_pair("float", 4));
	m_TypeSizeMap.insert(std::make_pair("double", 8));

	m_TypeSizeMap.insert(std::make_pair("NET_ITEM_INFO", 36));
	m_TypeSizeMap.insert(std::make_pair("NET_USER_INFO", 40));
	m_TypeSizeMap.insert(std::make_pair("NET_ROOM_INFO", 48));
	m_TypeSizeMap.insert(std::make_pair("NET_FRIEND_STATUS", 64));
	m_TypeSizeMap.insert(std::make_pair("NET_REQUEST_DATA", 32));
	m_TypeSizeMap.insert(std::make_pair("NET_SEAT_INFO", 32));
}

PokerMsgGen::~PokerMsgGen()
{
	// TODO: 
}

bool PokerMsgGen::CanPause(const char* pszTag)
{
	if (strcmp("PokerMsgs", pszTag) == 0) return true;
	return false;
}

bool PokerMsgGen::Parse(TiXmlElement* pElmRoot, const char* pszOutDir)
{
	TiXmlElement* pElmMsg = pElmRoot->FirstChildElement("message");
	while (pElmMsg)
	{
		MSG_INFO info;
		if (ParseXmlMessage(info, pElmMsg))
		{
			std::cout << "Generating " << info.pszClassName << " ..." << std::endl;
			GenerateClass(info, pszOutDir);
		}

		pElmMsg = pElmMsg->NextSiblingElement("message");
	}
	return true;
}

int PokerMsgGen::GetTypeSize(const char* pszType)
{
	TM_STRING_INT_MAP::iterator itfound = m_TypeSizeMap.find(pszType);
	if (itfound == m_TypeSizeMap.end()) return 0;
	return itfound->second;
}

bool PokerMsgGen::ParseXmlMessage(MSG_INFO& infoOut, TiXmlElement* pElmMessage)
{
	infoOut.pszClassName = pElmMessage->Attribute("name");
	if (!infoOut.pszClassName) return false;

	infoOut.pszMsgId = pElmMessage->Attribute("id");
	if (!infoOut.pszMsgId) return false;

	infoOut.nTotalDataSize = 0;
	TiXmlElement* pElmProperty = pElmMessage->FirstChildElement("property");
	while (pElmProperty)
	{
		PROPERTY_INFO prop;
		prop.pszName = pElmProperty->Attribute("name");
		prop.pszType = pElmProperty->Attribute("type");
		prop.nTypeSizeInByte = GetTypeSize(prop.pszType);
		if (prop.nTypeSizeInByte <= 0)
		{
			std::cout << "unknown type: " << prop.pszType << std::endl;
			return false;
		}

		prop.nArraySize = 1;
		pElmProperty->Attribute("array", &prop.nArraySize);
		if (prop.nArraySize < 1)
		{
			std::cout << "invalid array size: " << prop.nArraySize << " in property: " << prop.pszName << std::endl;
			return false;
		}

		infoOut.nTotalDataSize += (prop.nTypeSizeInByte * prop.nArraySize);
		infoOut.vPropertys.push_back(prop);

		pElmProperty = pElmProperty->NextSiblingElement("property");
	}

	return true;
}

bool PokerMsgGen::GenerateClass(const MSG_INFO& info, const char* pszDir)
{
	if (!GenerateH(info, pszDir)) return false;
	if (!GenerateCPP(info, pszDir)) return false;
	return true;
}

bool PokerMsgGen::GenerateH(const MSG_INFO& info, const char* pszDir)
{
	static const char* s_pszTemplate =
		"/*!\n"
		" * \\file %1.h\n"
		" * \\date unknown\n"
		" * \n"
		" * \n"
		" * \\author Auto Generate by MsgGen\n"
		" */\n"
		"#ifndef __%2_H__\n"
		"#define __%2_H__\n"
		"\n"
		"#include \"PokerMsgBase.h\"\n"
		"#include \"NetDataType.h\"\n"
		"\n"
		"class %1 : public PokerMsgBase\n"
		"{\n"
		"public:\n"
		"	enum CONST_DEFINE\n"
		"	{\n"
		"		MSG_TYPE = %3,\n"
		"		MSG_SIZE = %4,\n"
		"	};\n"
		"\n"
		"public:\n"
		"	DECLARE_RTTI(%1, PokerMsgBase);\n"
		"\n"
		"	%1();\n"
		"	virtual ~%1();\n"
		"\n"
		"	virtual bool Unpack(StreamReader* pReader);\n"
		"	virtual bool Pack(StreamWriter* pWriter);\n"
		"\n"
		"public:\n"
		"%5\n"
		"};\n"
		"\n"
		"#endif // __%2_H__\n";

	// class name
	std::string strContent = s_pszTemplate;
	StringReplace(strContent, "%1", info.pszClassName);

	// class name upper
	std::string strClassNameUpper = info.pszClassName;
	transform(strClassNameUpper.begin(), strClassNameUpper.end(), strClassNameUpper.begin(), ::toupper);
	StringReplace(strContent, "%2", strClassNameUpper.c_str());

	// message id
	StringReplace(strContent, "%3", info.pszMsgId);

	// message data size
	char szBuffer[128];
	_itoa_s(info.nTotalDataSize, szBuffer, 10);
	StringReplace(strContent, "%4", szBuffer);

	// message propertys
	std::string strPropertys;
	GenPropertysDeclare(strPropertys, info);
	StringReplace(strContent, "%5", strPropertys.c_str());

	// write into file
	std::string strFilePath = pszDir;
	strFilePath += info.pszClassName;
	strFilePath += ".h";
	FILE* pFileWrite = NULL;
	fopen_s(&pFileWrite, strFilePath.c_str(), "wb");
	fwrite(strContent.c_str(), 1, strContent.length(), pFileWrite);
	fclose(pFileWrite);

	return true;
}

bool PokerMsgGen::GenerateCPP(const MSG_INFO& info, const char* pszDir)
{
	static const char* s_pszTemplate =
		"/*!\n"
		" * \\file %1.cpp\n"
		" * \\date unknown\n"
		" * \n"
		" * \n"
		" * \\author Auto Generate by MsgGen\n"
		" */\n"
		"#include \"%1.h\"\n"
		"\n"
		"%1::%1()\n"
		":PokerMsgBase(MSG_TYPE, MSG_SIZE)\n"
		"{\n"
		"	// TODO: \n"
		"}\n"
		"\n"
		"%1::~%1()\n"
		"{\n"
		"	// TODO: \n"
		"}\n"
		"\n"
		"bool %1::Unpack(StreamReader* pReader)\n"
		"{\n"
		"%2	return true;\n"
		"}\n"
		"\n"
		"bool %1::Pack(StreamWriter* pWriter)\n"
		"{\n"
		"%3	return true;\n"
		"}\n";

	// class name
	std::string strContent = s_pszTemplate;
	StringReplace(strContent, "%1", info.pszClassName);

	// unpack
	std::string strUnpack;
	GenPropertysImplementUnpack(strUnpack, info);
	StringReplace(strContent, "%2", strUnpack.c_str());

	// pack
	std::string strPack;
	GenPropertysImplementPack(strPack, info);
	StringReplace(strContent, "%3", strPack.c_str());

	// write into file
	std::string strFilePath = pszDir;
	strFilePath += info.pszClassName;
	strFilePath += ".cpp";
	FILE* pFileWrite = NULL;
	fopen_s(&pFileWrite, strFilePath.c_str(), "wb");
	fwrite(strContent.c_str(), 1, strContent.length(), pFileWrite);
	fclose(pFileWrite);

	return true;
}

bool PokerMsgGen::GenPropertysDeclare(std::string& strInOut, const MSG_INFO& info)
{
	char szBuffer[128];

	for (TV_PROPERTY_INFO::const_iterator it = info.vPropertys.begin(); it != info.vPropertys.end(); ++it)
	{
		const PROPERTY_INFO& prop = (*it);
		strInOut += "\t";
		strInOut += prop.pszType;
		strInOut += " ";
		strInOut += prop.pszName;
		if (prop.nArraySize > 1)
		{
			strInOut += "[";
			_itoa_s(prop.nArraySize, szBuffer, 10);
			strInOut += szBuffer;
			strInOut += "];\n";
		}
		else
		{
			strInOut += ";\n";
		}
	}

	return true;
}

bool PokerMsgGen::GenPropertysImplementUnpack(std::string& strInOut, const MSG_INFO& info)
{
	for (TV_PROPERTY_INFO::const_iterator it = info.vPropertys.begin(); it != info.vPropertys.end(); ++it)
	{
		const PROPERTY_INFO& prop = (*it);
		strInOut += "\tif (!pReader->Read(&";
		strInOut += prop.pszName;
		strInOut += ", sizeof(";
		strInOut += prop.pszName;
		strInOut += "))) return false;\n";
	}

	return true;
}

bool PokerMsgGen::GenPropertysImplementPack(std::string& strInOut, const MSG_INFO& info)
{
	for (TV_PROPERTY_INFO::const_iterator it = info.vPropertys.begin(); it != info.vPropertys.end(); ++it)
	{
		const PROPERTY_INFO& prop = (*it);
		strInOut += "\tif (!pWriter->Write(&";
		strInOut += prop.pszName;
		strInOut += ", sizeof(";
		strInOut += prop.pszName;
		strInOut += "))) return false;\n";
	}

	return true;
}

void PokerMsgGen::StringReplace(std::string& strInOut, const char* pszFind, const char* pszReplace)
{
	int pos = strInOut.find(pszFind);
	int length = strlen(pszFind);
	if (!pszReplace) pszReplace = "";

	while (pos >= 0)
	{
		strInOut.replace(pos, length, pszReplace);
		pos = strInOut.find(pszFind);
	}
}
