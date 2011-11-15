/*!
 * \file MsgID.h
 * \date 8-10-2011 11:38:24
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGID_H__
#define __MSGID_H__

enum MESSAGE_ID
{
	MI_UNKNOWN = 0,
	MI_TEXTURE_DESTROIED,
	MI_SHADER_DESTROIED,
	MI_FONT_DESTROIED,
	MI_RENDERER_UI_FLUSH,
	MI_TOUCH,
	MI_KEY,
	MI_ACTION_UPDATE,
	MI_NET_MESSAGE,

	MI_UI_BEGIN,
	// leave the space for ui
	MI_UI_END = MI_UI_BEGIN+1000,

	MI_USER_DEFINE = 10000,
};

#endif // __MSGID_H__
