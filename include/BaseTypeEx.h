/*!
 * \file BaseTypeEx.h
 * \date 14-08-2011 11:03:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BASETYPEEX_H__
#define __BASETYPEEX_H__

#include "BaseType.h"

class ITexture;

enum BASETYPEEX_CONST_DEFINE
{
	MAX_ATTRIBUTE_NAME_LENGTH = 32,
	MAX_ATTRIBUTE_ITEMS = 8,
};

typedef struct VATTR_POS_UV_tag
{
	float x, y, z;
	float u, v;
} VATTR_POS_UV;

typedef struct QUAD_VERT_POS_UV_tag
{
	VATTR_POS_UV verts[4];
} QUAD_VERT_POS_UV;

typedef struct VATTR_POS_RGB_tag
{
	float x, y, z;
	float r, g, b;
} VATTR_POS_RGB;

typedef struct QUAD_VERT_POS_RGB_tag
{
	VATTR_POS_RGB verts[4];
} QUAD_VERT_POS_RGB;

typedef struct IMAGE_PIECE_tag
{
	float width, height;
	float u, v, du, dv;
	ITexture* pTexture;
} IMAGE_PIECE;

enum ATTRIBUTE_ITEM_TYPE
{
	AIT_UNKNOWN = 0,
	AIT_BYTE,
	AIT_UNSIGNED_BYTE,
	AIT_SHORT,
	AIT_UNSIGNED_SHORT,
	AIT_FLOAT,
	AIT_FIXED,
	AIT_HALF_FLOAT_OES,
	NUM_AIT,
};

typedef struct ATTRIBUTE_ITEM_tag
{
	uint nSize;
	ATTRIBUTE_ITEM_TYPE eItemType;
	uint nOffset;
	char szParamName[MAX_ATTRIBUTE_NAME_LENGTH];
} ATTRIBUTE_ITEM;

enum TEXTURE_SAMPLE_TYPE
{
	TST_POINT = 0,
	TST_LINEAR,
};

enum SYSTEM_SHADER_IDS
{
	SSI_DEFAULT = 1,
};

enum ACTION_UPDATE_TYPE
{
	AUT_UNKNOWN = 0,

	AUT_SCALE,
	AUT_POSITION,
	AUT_ROTATION,

	AUT_START,
	AUT_PAUSE,
	AUT_STOPED,

	AUT_SUBACTION_START,
	AUT_SUBACTION_PAUSE,
	AUT_SUBACTION_STOPED,
};

enum ACTION_TWEEN_TYPE
{
	ATT_EASE_IN = 0,
	ATT_EASE_OUT,
	ATT_EASE_IN_OUT,
};
#endif // __BASETYPEEX_H__
