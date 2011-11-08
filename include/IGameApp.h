/*!
 * \file IGameApp.h
 * \date 24-07-2011 11:21:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IGAMEAPP_H__
#define __IGAMEAPP_H__

#include "BaseType.h"
#include "ISingleton.h"

class IGameApp : public ISingleton
{
public:
	DECLARE_RTTI(IGameApp, ISingleton);

	static IGameApp& GetInstance();

};
#endif // __IGAMEAPP_H__
