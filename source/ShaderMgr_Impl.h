/*!
 * \file ShaderMgr_Impl.h
 * \date 7-25-2011 10:15:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SHADERMGR_IMPL_H__
#define __SHADERMGR_IMPL_H__

#include <IShaderMgr.h>
#include <msg/IMsgBase.h>
#include <map>

class ShaderMgr_Impl : public IShaderMgr
{
public:
	typedef std::map<int, IShader*> TM_SHADER;

public:
	DECLARE_RTTI(ShaderMgr_Impl, IShaderMgr);

	ShaderMgr_Impl();
	virtual ~ShaderMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual IShader* CreateShader(const char* pszShaderFile);
	virtual IShader* CreateShader(int nShaderID = SSI_DEFAULT);

private:
	IShader* InternalCreateShader(int nShaderID, const char* pszVertexShaderFile, const char* pszFregmentShaderFile, const ATTRIBUTE_ITEM* pAttrItems);
	VertexAttribute* InternalCreateVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);
	IShader* FindShader(int nID);
	bool OnShaderDestroied(IMsgBase* pMsg);

private:
	TM_SHADER m_mapShader;
	IShader* m_pDefaultShader;

};
#endif // __SHADERMGR_IMPL_H__
