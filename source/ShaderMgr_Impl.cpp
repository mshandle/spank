/*!
 * \file ShaderMgr_Impl.cpp
 * \date 7-25-2011 10:16:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ShaderMgr_Impl.h"
#include "Shader_Impl.h"
#include <util/IFileUtil.h>
#include <util/IDebugUtil.h>
#include <util/StringUtil.h>
#include <msg/MsgID.h>
#include <msg/MsgCommon.h>
#include <tinyxml-2.6.2/tinyxml.h>

IShaderMgr& IShaderMgr::GetInstance()
{
	static ShaderMgr_Impl s_ShaderMgr_Impl;
	return s_ShaderMgr_Impl;
}

ShaderMgr_Impl::ShaderMgr_Impl()
{
	// TODO: 
}

ShaderMgr_Impl::~ShaderMgr_Impl()
{
	// TODO: 
}

bool ShaderMgr_Impl::Initialize()
{
	CreateShader("default_shader.xml");
	return true;
}

void ShaderMgr_Impl::Terminate()
{
	// TODO: 
}

IShader* ShaderMgr_Impl::CreateShader(const char* pszShaderFile)
{
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszShaderFile);
	if (!pReader) return NULL;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);
	if (doc.Error()) return NULL;

	// parse the xml files
	TiXmlElement* pElmShader = doc.RootElement();
	if (!pElmShader) return NULL;

	int nShaderID = 0;
	pElmShader->Attribute("id", &nShaderID);
	if (nShaderID <= 0) return NULL;

	IShader* pShader = FindShader(nShaderID);
	if (pShader)
	{
		pShader->IncRef();
		return pShader;
	}

	const char* pszVertexShader = NULL;
	pszVertexShader = pElmShader->Attribute("vertex_shader");
	if (!pszVertexShader) return NULL;

	const char* pszFregmentShader = NULL;
	pszFregmentShader = pElmShader->Attribute("fregment_shader");
	if (!pszFregmentShader) return NULL;

	TiXmlElement* pElmAttrs = pElmShader->FirstChildElement("attributes");
	if (!pElmAttrs) return NULL;

	ATTRIBUTE_ITEM attrItems[MAX_ATTRIBUTE_ITEMS+1];
	int nAttrIndex = 0;

	TiXmlElement* pElmAttr = pElmAttrs->FirstChildElement("attribute");
	while (pElmAttr)
	{
		int nSize = 0;
		pElmAttr->Attribute("size", &nSize);
		if (nSize <= 0) return NULL;

		const char* pszAttrName = pElmAttr->Attribute("name");
		if (!pszAttrName) return NULL;

		attrItems[nAttrIndex].nSize = nSize;
		attrItems[nAttrIndex].eItemType = AIT_FLOAT;
		StringUtil::CopyString(attrItems[nAttrIndex].szParamName, MAX_ATTRIBUTE_NAME_LENGTH, pszAttrName);

		++nAttrIndex;
		pElmAttr = pElmAttr->NextSiblingElement("attribute");
	}

	if (nAttrIndex <= 0) return NULL;

	attrItems[nAttrIndex].nSize = 0;
	attrItems[nAttrIndex].eItemType = AIT_UNKNOWN;
	attrItems[nAttrIndex].nOffset = 0;
	attrItems[nAttrIndex].szParamName[0] = '\0';

	return InternalCreateShader(nShaderID, pszVertexShader, pszFregmentShader, attrItems);
}

IShader* ShaderMgr_Impl::CreateShader(int nShaderID /* = SSI_DEFAULT */)
{
	IShader* pShader = FindShader(nShaderID);
	if (pShader)
	{
		pShader->IncRef();
		return pShader;
	}

	return NULL;
}

IShader* ShaderMgr_Impl::InternalCreateShader(int nShaderID, const char* pszVertexShaderFile, const char* pszFregmentShaderFile, const ATTRIBUTE_ITEM* pAttrItems)
{
	StreamReader* pVertexShader = IFileUtil::GetInstance().LoadFile(pszVertexShaderFile);
	if (!pVertexShader || !pVertexShader->IsOK())
	{
		SAFE_RELEASE(pVertexShader);
		return NULL;
	}

	StreamReader* pFregmentShader = IFileUtil::GetInstance().LoadFile(pszFregmentShaderFile);
	if (!pFregmentShader || !pFregmentShader->IsOK())
	{
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pFregmentShader);
		return NULL;
	}

	VertexAttribute* pVertAttrib = InternalCreateVertexAttribute(pAttrItems);
	if (!pVertAttrib || !pVertAttrib->IsOK())
	{
		SAFE_RELEASE(pVertAttrib);
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pFregmentShader);

		LOGE("create vertex attribute failed");
		return NULL;
	}

	Shader_Impl* pShader = new Shader_Impl(pVertexShader, pFregmentShader, pVertAttrib);
	if (!pShader || !pShader->IsOK())
	{
		SAFE_DELETE(pShader);
		SAFE_RELEASE(pVertAttrib);
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pFregmentShader);

		LOGE("create shader failed");
		return NULL;
	}

	// connect the destroy event
	pShader->ConnectEvent(MI_SHADER_DESTROIED, this, (MSG_CALLBACK)&ShaderMgr_Impl::OnShaderDestroied);
	// cache the shader
	m_mapShader.insert(std::make_pair(nShaderID, pShader));

	return pShader;
}

VertexAttribute* ShaderMgr_Impl::InternalCreateVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems)
{
	VertexAttribute* pVertAttr = new VertexAttribute(pAttrItems);
	if (!pVertAttr || !pVertAttr->IsOK())
	{
		SAFE_DELETE(pVertAttr);
		return NULL;
	}

	return pVertAttr;
}

IShader* ShaderMgr_Impl::FindShader(int nID)
{
	TM_SHADER::iterator itfound = m_mapShader.find(nID);
	if (itfound == m_mapShader.end()) return NULL;

	return itfound->second;
}

bool ShaderMgr_Impl::OnShaderDestroied(IMsgBase* pMsg)
{
	MsgCommon* pMsgCommon = (MsgCommon*)pMsg;
	IShader* pShader = (IShader*)pMsgCommon->GetObject();
	if (!pShader) return false;

	for (TM_SHADER::iterator it = m_mapShader.begin(); it != m_mapShader.end(); ++it)
	{
		if (it->second == pShader)
		{
			m_mapShader.erase(it);
			return true;
		}
	}

	return false;
}
