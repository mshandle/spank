/*!
 * \file Config.h
 * \date 2-17-2012 10:20:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CONFIG_H__
#define __CONFIG_H__

#include <wx/string.h>

class Config
{
public:
	enum CONST_DEFINE
	{
		DEFAULT_IMAGE_SIZE = 512,
		DEFAULT_PIECE_SIZE = 100,
		DEFAULT_COLOR = 0x808080,
		DISABLED_PEN_WIDTH = 3,
	};

public:
	static wxString m_strAbout;

};
#endif // __CONFIG_H__
