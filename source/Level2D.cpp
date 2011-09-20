/*!
 * \file Level2D.cpp
 * \date 08-08-2011 22:49:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <Level2D.h>
#include <math/IMath.h>
#include <util/IFileUtil.h>
#include <util/ScreenUtil.h>
#include <ITextureMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>

Level2D::Level2D(const char* pszLevel2DFile)
{
	m_vCenterPosition = IMath::VEC2_ZERO;
	m_nPrvCenterPositionX = 0;
	m_nPrvCenterPositionY = 0;

	m_nHalfSceneHeight = ScreenUtil::GetInstance().GetScreenHeight() / 2;
	m_nHalfSceneWidth = ScreenUtil::GetInstance().GetScreenWidth() / 2;
	m_nSurfaceColTileNum = 0;
	m_nSurfaceRowTileNum = 0;
	
	m_pTexture = NULL;
	m_pIndis = NULL;
	m_pVerts = NULL;
	m_pShader = NULL;
	m_pGidAry = NULL;
	m_pTileInfo = NULL;
	m_bOK = LoadLevel2DFromFile(pszLevel2DFile);
}

Level2D::~Level2D()
{
	SAFE_RELEASE(m_pTexture);
	SAFE_RELEASE(m_pShader);
	SAFE_DELETE_ARRAY(m_pVerts);
	SAFE_DELETE_ARRAY(m_pGidAry);
	SAFE_DELETE_ARRAY(m_pTileInfo);
	SAFE_DELETE_ARRAY(m_pIndis);
}

void Level2D::Update(float dt)
{
	int nXBoundary = (TILE_BORDER_SIZE + m_nHalfSceneWidth / m_FileHeader.nTileWidth) * m_FileHeader.nTileWidth - m_nHalfSceneWidth;
	int nYBoundary = (TILE_BORDER_SIZE + m_nHalfSceneHeight / m_FileHeader.nTileHeight) * m_FileHeader.nTileHeight - m_nHalfSceneHeight;
	
	if((m_vCenterPosition.x - m_nPrvCenterPositionX > nXBoundary)
		|| (m_vCenterPosition.x - m_nPrvCenterPositionX < -nXBoundary)
		|| (m_vCenterPosition.y - m_nPrvCenterPositionY > nYBoundary)
		|| (m_vCenterPosition.y - m_nPrvCenterPositionY < -nYBoundary))
	{
		m_nPrvCenterPositionX =  int(m_vCenterPosition.x / (int)m_FileHeader.nTileWidth) * (int)m_FileHeader.nTileWidth;
		m_nPrvCenterPositionY =  int(m_vCenterPosition.y / (int)m_FileHeader.nTileHeight) * (int)m_FileHeader.nTileHeight;
		
		UpdateVerts();
	}
}

void Level2D::Render()
{
	m_pShader->SetTexture("u_texture",m_pTexture);

	Vector2 vecTranslate(m_vCenterPosition.x - m_nPrvCenterPositionX, m_vCenterPosition.y - m_nPrvCenterPositionY);

	vecTranslate.x = float((int)vecTranslate.x);
	vecTranslate.y = float((int)vecTranslate.y);
	Matrix4x4 matModelView;
	IMath::BuildTranslateMatrix(matModelView, -vecTranslate.x, -vecTranslate.y, 0.0f);
	IRenderer2D::GetInstance().SetModelViewMatrix(matModelView);
	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	uint unRectSize = m_nSurfaceRowTileNum * m_nSurfaceColTileNum;
	IRenderer2D::GetInstance().DrawTriangleList(m_pVerts, unRectSize * VERTEX_CACHE_SIZE, m_pIndis, unRectSize * INDEX_CACHE_SIZE, m_pShader);

}

void Level2D::SetCenterPosition(const Vector2& pos)
{
	m_vCenterPosition = pos;
}

const Vector2& Level2D::GetCenterPosition() const
{
	return m_vCenterPosition;
}

bool Level2D::LoadLevel2DFromFile(const char* pszLevel2DFile)
{
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszLevel2DFile);
	if (!pReader) return false;

	pReader->Read(&m_FileHeader, sizeof(m_FileHeader));
	// TODO: check file valid

	m_pTileInfo = new FmtL2D::TILE_INFO[m_FileHeader.nNumTiles];
	pReader->Read(m_pTileInfo, sizeof(FmtL2D::TILE_INFO) * m_FileHeader.nNumTiles);

	m_pGidAry = new uint[m_FileHeader.nMapCol * m_FileHeader.nMapRow];
	pReader->Read(m_pGidAry, sizeof(uint) * m_FileHeader.nMapCol * m_FileHeader.nMapRow);
	SAFE_RELEASE(pReader);

	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if(!m_pShader) return false;

	m_pTexture = ITextureMgr::GetInstance().CreateTexture(m_FileHeader.szTextureFile);
	if(NULL == m_pTexture) return false;

	m_nSurfaceColTileNum = (m_nHalfSceneWidth / m_FileHeader.nTileWidth) * 2 + TILE_BORDER_SIZE * 2;
	m_nSurfaceRowTileNum = (m_nHalfSceneHeight / m_FileHeader.nTileHeight) * 2 + TILE_BORDER_SIZE * 2;
	
	InitVerts();
	return true;
}

void Level2D::GetMapCoordinateIndex(Vector2& MapPosition, int& nXindex, int& nYindex)
{
	MapPosition.x = m_FileHeader.nMapCol * m_FileHeader.nTileWidth  / 2.0f + MapPosition.x;
	MapPosition.y = m_FileHeader.nMapRow * m_FileHeader.nTileHeight / 2.0f - MapPosition.y;
	nXindex = (int)MapPosition.x / (int)m_FileHeader.nTileWidth;
	nYindex = (int)MapPosition.y / (int)m_FileHeader.nTileHeight;
}

void Level2D::InitVerts()
{
	m_pVerts = new VATTR_POS_UV[m_nSurfaceColTileNum * m_nSurfaceRowTileNum * VERTEX_CACHE_SIZE];
	m_pIndis = new ushort[m_nSurfaceColTileNum * m_nSurfaceRowTileNum * INDEX_CACHE_SIZE];

	float fXstartCoord = -float(m_nSurfaceColTileNum / 2.0f) * m_FileHeader.nTileWidth;
	float fYstartCoord =  float(m_nSurfaceRowTileNum / 2.0f) * m_FileHeader.nTileHeight;

	int nTileInMapColIndex = 0;
	int nTileInMapRowIndex = 0;

	Vector2 TextTrueCoordinate(fXstartCoord + m_nPrvCenterPositionX, fYstartCoord + m_nPrvCenterPositionY);
	GetMapCoordinateIndex(TextTrueCoordinate, nTileInMapColIndex, nTileInMapRowIndex);

	for (int v1 = 0; v1 < m_nSurfaceRowTileNum; ++v1)
	{
		for (int v2 = 0; v2 < m_nSurfaceColTileNum; ++v2)
		{
			uint unIndisOffNumber = v1 * m_nSurfaceColTileNum * INDEX_CACHE_SIZE + v2 * INDEX_CACHE_SIZE;
			uint nVertsOffNumber = v1 * m_nSurfaceColTileNum * VERTEX_CACHE_SIZE + v2 * VERTEX_CACHE_SIZE;
			
			m_pIndis[unIndisOffNumber + 0] = nVertsOffNumber + 0;
			m_pIndis[unIndisOffNumber + 1] = nVertsOffNumber + 1;
			m_pIndis[unIndisOffNumber + 2] = nVertsOffNumber + 2;
			m_pIndis[unIndisOffNumber + 3] = nVertsOffNumber + 1;
			m_pIndis[unIndisOffNumber + 4] = nVertsOffNumber + 3;
			m_pIndis[unIndisOffNumber + 5] = nVertsOffNumber + 2;

			uint unTileIndexNumber = 0;

			if (nTileInMapColIndex < (int)m_FileHeader.nMapCol
				&&nTileInMapColIndex >= 0
				&&nTileInMapRowIndex < (int)m_FileHeader.nMapRow
				&&nTileInMapRowIndex >= 0)
			{
				unTileIndexNumber = m_pGidAry[nTileInMapRowIndex * m_FileHeader.nMapCol + nTileInMapColIndex];
			}
			else
			{
				unTileIndexNumber = m_FileHeader.nDefaultTile;
			}

			m_pVerts[nVertsOffNumber + 0].x = fXstartCoord;
			m_pVerts[nVertsOffNumber + 0].y = fYstartCoord - m_FileHeader.nTileHeight;
			m_pVerts[nVertsOffNumber + 0].z = 0.0f;
			m_pVerts[nVertsOffNumber + 0].u = m_pTileInfo[unTileIndexNumber].u;
			m_pVerts[nVertsOffNumber + 0].v = m_pTileInfo[unTileIndexNumber].v;

			m_pVerts[nVertsOffNumber + 1].x = fXstartCoord;
			m_pVerts[nVertsOffNumber + 1].y = fYstartCoord;
			m_pVerts[nVertsOffNumber + 1].z = 0.0f;
			m_pVerts[nVertsOffNumber + 1].u = m_pTileInfo[unTileIndexNumber].u;
			m_pVerts[nVertsOffNumber + 1].v = m_pTileInfo[unTileIndexNumber].v + m_pTileInfo[unTileIndexNumber].dv;

			m_pVerts[nVertsOffNumber + 2].x = fXstartCoord + m_FileHeader.nTileWidth;
			m_pVerts[nVertsOffNumber + 2].y = fYstartCoord - m_FileHeader.nTileHeight;
			m_pVerts[nVertsOffNumber + 2].z = 0.0f;
			m_pVerts[nVertsOffNumber + 2].u = m_pTileInfo[unTileIndexNumber].u + m_pTileInfo[unTileIndexNumber].du;
			m_pVerts[nVertsOffNumber + 2].v = m_pTileInfo[unTileIndexNumber].v; 

			m_pVerts[nVertsOffNumber + 3].x = fXstartCoord + m_FileHeader.nTileWidth;
			m_pVerts[nVertsOffNumber + 3].y = fYstartCoord;
			m_pVerts[nVertsOffNumber + 3].z = 0.0f;
			m_pVerts[nVertsOffNumber + 3].u = m_pTileInfo[unTileIndexNumber].u + m_pTileInfo[unTileIndexNumber].du;
			m_pVerts[nVertsOffNumber + 3].v = m_pTileInfo[unTileIndexNumber].v + m_pTileInfo[unTileIndexNumber].dv;
			
			fXstartCoord += m_FileHeader.nTileWidth;
			nTileInMapColIndex++;
		}//for ( int v2=0; v2 < nXTileSize; v2++ )

		nTileInMapColIndex -= m_nSurfaceColTileNum;
		nTileInMapRowIndex++;
		fXstartCoord = - (float)(m_nSurfaceColTileNum / 2.0f) * m_FileHeader.nTileWidth;
		fYstartCoord -= m_FileHeader.nTileHeight;
	}//for(int v1=0; v1 < nYTileSize; v1++)
}

void Level2D::UpdateVerts()
{
	float fXstartCoord = -float(m_nSurfaceColTileNum / 2.0f) * m_FileHeader.nTileWidth;
	float fYstartCoord =  float(m_nSurfaceRowTileNum / 2.0f) * m_FileHeader.nTileHeight;

	int nTileInMapColIndex = 0;
	int nTileInMapRowIndex = 0;
	Vector2 TextTrueCoordinate;
	TextTrueCoordinate.x = fXstartCoord + m_nPrvCenterPositionX;
	TextTrueCoordinate.y = fYstartCoord + m_nPrvCenterPositionY;
	GetMapCoordinateIndex(TextTrueCoordinate, nTileInMapColIndex, nTileInMapRowIndex);

	for (int v1 = 0; v1 < m_nSurfaceRowTileNum; ++v1)
	{
		for (int v2 = 0; v2 < m_nSurfaceColTileNum; ++v2)
		{
			uint unVertsOffNumber = v1 * m_nSurfaceColTileNum * VERTEX_CACHE_SIZE + v2 * VERTEX_CACHE_SIZE;
			uint unTileIndexNumber = 0;
			
			if(nTileInMapColIndex < (int)m_FileHeader.nMapCol
				&&nTileInMapColIndex >= 0
				&&nTileInMapRowIndex < (int)m_FileHeader.nMapRow
				&&nTileInMapRowIndex >= 0)
			{
				unTileIndexNumber = m_pGidAry[nTileInMapRowIndex* m_FileHeader.nMapCol + nTileInMapColIndex];
			}
			else
			{
				unTileIndexNumber = m_FileHeader.nDefaultTile;
			}

			m_pVerts[unVertsOffNumber + 0].u = m_pTileInfo[unTileIndexNumber].u;
			m_pVerts[unVertsOffNumber + 0].v = m_pTileInfo[unTileIndexNumber].v;
			
			m_pVerts[unVertsOffNumber + 1].u = m_pTileInfo[unTileIndexNumber].u;
			m_pVerts[unVertsOffNumber + 1].v = m_pTileInfo[unTileIndexNumber].v + m_pTileInfo[unTileIndexNumber].dv;
			
			m_pVerts[unVertsOffNumber + 2].u = m_pTileInfo[unTileIndexNumber].u + m_pTileInfo[unTileIndexNumber].du;
			m_pVerts[unVertsOffNumber + 2].v = m_pTileInfo[unTileIndexNumber].v; 
			
			m_pVerts[unVertsOffNumber + 3].u = m_pTileInfo[unTileIndexNumber].u + m_pTileInfo[unTileIndexNumber].du;
			m_pVerts[unVertsOffNumber + 3].v = m_pTileInfo[unTileIndexNumber].v + m_pTileInfo[unTileIndexNumber].dv;
			
			fXstartCoord += m_FileHeader.nTileWidth;
			nTileInMapColIndex++;
		}

		nTileInMapColIndex -= m_nSurfaceColTileNum;
		nTileInMapRowIndex++;
		fXstartCoord = - (float)(m_nSurfaceColTileNum / 2.0f) * m_FileHeader.nTileWidth;
		fYstartCoord -= m_FileHeader.nTileHeight;
	}
}
