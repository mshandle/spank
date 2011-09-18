/*!
 * \file SnowParticleSystem.cpp
 * \date 8-18-2011 10:26:07
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <particle/SnowParticleSystem.h>
#include <particle/SnowParticle.h>
#include <IRenderer2D.h>
#include <IResourceMgr.h>
#include <IShaderMgr.h>
#include <ITextureMgr.h>

SnowParticleSystem::SnowParticleSystem(const char* pszImagePiece)
{
	m_pSnowEmmiter = NULL;
	m_pVerts = NULL;
	m_pIndis = NULL;
	m_pShader = NULL;
	m_pImagePiece = NULL;

	m_bOK = Init(pszImagePiece);
}

SnowParticleSystem::~SnowParticleSystem()
{
	SAFE_DELETE(m_pSnowEmmiter);
	SAFE_DELETE_ARRAY(m_pVerts);
	SAFE_DELETE_ARRAY(m_pIndis);
	SAFE_RELEASE(m_pShader);
}

void SnowParticleSystem::Update(float dt)
{
	m_pSnowEmmiter->Update(dt);

	TV_PARTICLE::iterator it = m_vParticles.begin();
	while (it != m_vParticles.end())
	{
		IParticle* pParticle = (*it);
		pParticle->Update(dt);
		if (!pParticle->IsAlive())
		{
			m_pSnowEmmiter->RecycleParticle(pParticle);
			it = m_vParticles.erase(it);
		}
		else
		{
			++it;
		}
	}

	int nNumEmmit = m_pSnowEmmiter->PopNumEmmit();
	for (int i = 0; i < nNumEmmit; ++i)
	{
		IParticle* pParticle = m_pSnowEmmiter->CreateParticle();
		if (pParticle)
		{
			pParticle->Start();
			m_vParticles.push_back(pParticle);
		}
	}
}

void SnowParticleSystem::Render()
{
	int nNumVerts = 0;
	int nNumIndis = 0;

	for (TV_PARTICLE::iterator it = m_vParticles.begin(); it != m_vParticles.end(); ++it)
	{
		SnowParticle* pParticle = (SnowParticle*)(*it);

		m_pVerts[nNumVerts+0].x = pParticle->m_vPosition.x - pParticle->m_vSize.x;
		m_pVerts[nNumVerts+0].y = pParticle->m_vPosition.y - pParticle->m_vSize.y;

		m_pVerts[nNumVerts+1].x = pParticle->m_vPosition.x - pParticle->m_vSize.x;
		m_pVerts[nNumVerts+1].y = pParticle->m_vPosition.y + pParticle->m_vSize.y;

		m_pVerts[nNumVerts+2].x = pParticle->m_vPosition.x + pParticle->m_vSize.x;
		m_pVerts[nNumVerts+2].y = pParticle->m_vPosition.y - pParticle->m_vSize.y;

		m_pVerts[nNumVerts+3].x = pParticle->m_vPosition.x + pParticle->m_vSize.x;
		m_pVerts[nNumVerts+3].y = pParticle->m_vPosition.y + pParticle->m_vSize.y;

		nNumVerts += 4;
		nNumIndis += 6;

		if (nNumVerts >= VERTEX_CACHE_SIZE)
		{
			m_pShader->SetTexture("u_texture", m_pImagePiece->pTexture);

			IRenderer2D::GetInstance().SetModelViewMatrix(IMath::MAT4X4_IDENTITY);
			m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

			IRenderer2D::GetInstance().DrawTriangleList(m_pVerts, nNumVerts, m_pIndis, nNumIndis, m_pShader);
			nNumVerts = 0;
			nNumIndis = 0;
		}
	}

	if (nNumVerts > 0)
	{
		m_pShader->SetTexture("u_texture", m_pImagePiece->pTexture);

		IRenderer2D::GetInstance().SetModelViewMatrix(IMath::MAT4X4_IDENTITY);
		m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

		IRenderer2D::GetInstance().DrawTriangleList(m_pVerts, nNumVerts, m_pIndis, nNumIndis, m_pShader);
		nNumVerts = 0;
		nNumIndis = 0;
	}
}

bool SnowParticleSystem::Init(const char* pszImagePiece)
{
	m_pSnowEmmiter = new SnowEmmiter();

	m_pVerts = new VATTR_POS_UV[VERTEX_CACHE_SIZE];
	m_pIndis = new ushort[INDEX_CACHE_SIZE];

	m_pShader = IShaderMgr::GetInstance().CreateShader();
	if (!m_pShader) return false;

	m_pImagePiece = IResourceMgr::GetInstance().FindImagePiece(pszImagePiece);
	if (!m_pImagePiece) return false;

	for (int i = 0; i < NUM_PARTICLE; ++i)
	{
		int nVertsIndexBase = i*4;
		m_pVerts[nVertsIndexBase+0].x = 0.0f;
		m_pVerts[nVertsIndexBase+0].y = 0.0f;
		m_pVerts[nVertsIndexBase+0].z = 0.0f;
		m_pVerts[nVertsIndexBase+0].u = m_pImagePiece->u;
		m_pVerts[nVertsIndexBase+0].v = m_pImagePiece->v;

		m_pVerts[nVertsIndexBase+1].x = 0.0f;
		m_pVerts[nVertsIndexBase+1].y = 0.0f;
		m_pVerts[nVertsIndexBase+1].z = 0.0f;
		m_pVerts[nVertsIndexBase+1].u = m_pImagePiece->u;
		m_pVerts[nVertsIndexBase+1].v = m_pImagePiece->v+m_pImagePiece->dv;

		m_pVerts[nVertsIndexBase+2].x = 0.0f;
		m_pVerts[nVertsIndexBase+2].y = 0.0f;
		m_pVerts[nVertsIndexBase+2].z = 0.0f;
		m_pVerts[nVertsIndexBase+2].u = m_pImagePiece->u+m_pImagePiece->du;
		m_pVerts[nVertsIndexBase+2].v = m_pImagePiece->v;

		m_pVerts[nVertsIndexBase+3].x = 0.0f;
		m_pVerts[nVertsIndexBase+3].y = 0.0f;
		m_pVerts[nVertsIndexBase+3].z = 0.0f;
		m_pVerts[nVertsIndexBase+3].u = m_pImagePiece->u+m_pImagePiece->du;
		m_pVerts[nVertsIndexBase+3].v = m_pImagePiece->v+m_pImagePiece->dv;

		int nIndisIndexBase = i*6;
		m_pIndis[nIndisIndexBase+0] = nVertsIndexBase+0;
		m_pIndis[nIndisIndexBase+1] = nVertsIndexBase+1;
		m_pIndis[nIndisIndexBase+2] = nVertsIndexBase+2;
		m_pIndis[nIndisIndexBase+3] = nVertsIndexBase+1;
		m_pIndis[nIndisIndexBase+4] = nVertsIndexBase+3;
		m_pIndis[nIndisIndexBase+5] = nVertsIndexBase+2;
	}

	return true;
}
