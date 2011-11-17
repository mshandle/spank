/*!
 * \file MsgGenFactory.cpp
 * \date 11-17-2011 13:58:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "MsgGenFactory.h"
#include "PokerMsgGen.h"

MsgGenFactory& MsgGenFactory::GetInstance()
{
	static MsgGenFactory s_MsgGenFactory;
	return s_MsgGenFactory;
}

MsgGenFactory::MsgGenFactory()
{
	// TODO: 
}

MsgGenFactory::~MsgGenFactory()
{
	// TODO: 
}

bool MsgGenFactory::Initialize()
{
	AddParser(new PokerMsgGen());

	return true;
}

void MsgGenFactory::Terminate()
{
	for (TV_MSG_GEN::iterator it = m_vGens.begin(); it != m_vGens.end(); ++it)
	{
		IMsgGen* pMsgGen = (*it);
		delete pMsgGen;
	}
	m_vGens.clear();
}

bool MsgGenFactory::Parse(const char* pszFile, const char* pszOutDir)
{
	TiXmlDocument doc(pszFile);
	doc.LoadFile();
	if(doc.Error()) return false;

	TiXmlElement* pElmRoot = doc.RootElement();
	if (!pElmRoot) return false;

	IMsgGen* pMsgGen = FindParser(pElmRoot->Value());
	if (!pMsgGen) return false;

	return pMsgGen->Parse(pElmRoot, pszOutDir);
}

IMsgGen* MsgGenFactory::FindParser(const char* pszTag)
{
	for (TV_MSG_GEN::iterator it = m_vGens.begin(); it != m_vGens.end(); ++it)
	{
		IMsgGen* pMsgGen = (*it);
		if (pMsgGen->CanPause(pszTag)) return pMsgGen;
	}

	return NULL;
}

void MsgGenFactory::AddParser(IMsgGen* pMsgGen)
{
	m_vGens.push_back(pMsgGen);
}
