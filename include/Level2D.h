/*!
 * \file Level2D.h
 * \date 08-08-2011 22:47:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __LEVEL2D_H__
#define __LEVEL2D_H__

#include <IRenderableObject.h>
#include <ITexture.h>
#include <IShader.h>
#include <BaseTypeEx.h>
#include <fileformat/FmtL2D.h>
#include <math/IMath.h>

class Level2D : public IRenderableObject
{
public:
	enum CONST_DEFINE
	{
		TILE_BORDER_SIZE = 4,
		VERTEX_CACHE_SIZE = 4,
		INDEX_CACHE_SIZE = 6,
	};

public:
	DECLARE_RTTI(Level2D, IRenderableObject);

	Level2D(const char* pszLevel2DFile);
	virtual ~Level2D();
	
	virtual void Update(float dt);
	virtual void Render();

	void SetCenterPosition(const Vector2& pos);
	const Vector2& GetCenterPosition() const;

private:
	void InitVerts();
	void UpdateVerts();
	bool LoadLevel2DFromFile(const char* pszLevel2DFile);
	void GetMapCoordinateIndex(Vector2& MapPosition, int& nXindex, int& nYindex);

private:
	Vector2 m_vCenterPosition;		
	int m_nPrvCenterPositionX;
	int m_nPrvCenterPositionY;

	int m_nHalfSceneWidth;
	int m_nHalfSceneHeight;

	int m_nSurfaceColTileNum;
	int m_nSurfaceRowTileNum;

	IShader* m_pShader;				
	ITexture* m_pTexture;

	ushort* m_pIndis;
	VATTR_POS_UV* m_pVerts;	

	FmtL2D::FILE_HEADER m_FileHeader;
	FmtL2D::TILE_INFO* m_pTileInfo;
	uint* m_pGidAry;
	
};
#endif // __LEVEL2D_H__
