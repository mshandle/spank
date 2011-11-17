/*!
 * \file IMsgGen.h
 * \date 11-17-2011 13:54:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMSGGEN_H__
#define __IMSGGEN_H__

#include <tinyxml.h>

class IMsgGen
{
public:
	IMsgGen();
	virtual ~IMsgGen();

	virtual bool CanPause(const char* pszTag) = 0;
	virtual bool Parse(TiXmlElement* pElmRoot, const char* pszOutDir) = 0;

};
#endif // __IMSGGEN_H__
