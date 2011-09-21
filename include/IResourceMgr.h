/*!
 * \file IResourceMgr.h
 * \date 12-09-2011 16:42:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRESOURCEMGR_H__
#define __IRESOURCEMGR_H__

#include "ISingleton.h"
#include "BaseTypeEx.h"

class IResourceMgr : public ISingleton
{
public:
	DECLARE_RTTI(IResourceMgr, ISingleton);

	static IResourceMgr& GetInstance();

	virtual bool AddImagePieceList(const char* pszFile) = 0;
	virtual bool RemoveImagePieceList(const char* pszFile) = 0;
	virtual const IMAGE_PIECE* FindImagePiece(const char* pszName) = 0;

};
#endif // __IRESOURCEMGR_H__
