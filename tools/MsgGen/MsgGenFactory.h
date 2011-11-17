/*!
 * \file MsgGenFactory.h
 * \date 11-17-2011 13:53:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGGENFACTORY_H__
#define __MSGGENFACTORY_H__

#include "IMsgGen.h"
#include <vector>

class MsgGenFactory
{
public:
	typedef std::vector<IMsgGen*> TV_MSG_GEN;

public:
	MsgGenFactory();
	~MsgGenFactory();

	static MsgGenFactory& GetInstance();

	bool Initialize();
	void Terminate();

	bool Parse(const char* pszFile, const char* pszOutDir);

private:
	IMsgGen* FindParser(const char* pszTag);
	void AddParser(IMsgGen* pMsgGen);

private:
	TV_MSG_GEN m_vGens;

};
#endif // __MSGGENFACTORY_H__
