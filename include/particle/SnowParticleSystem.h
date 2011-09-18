/*!
 * \file SnowParticleSystem.h
 * \date 8-18-2011 10:26:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SNOWPARTICLESYSTEM_H__
#define __SNOWPARTICLESYSTEM_H__

#include "IParticleSystem.h"
#include "SnowEmmiter.h"
#include "../BaseTypeEx.h"
#include "../IShader.h"
#include "../ITexture.h"
#include <vector>

class SnowParticleSystem : public IParticleSystem
{
public:
	enum CONST_DEFINE
	{
		NUM_PARTICLE = 64,
		VERTEX_CACHE_SIZE = NUM_PARTICLE * 4,
		INDEX_CACHE_SIZE = NUM_PARTICLE * 6,
	};

	typedef std::vector<IParticle*> TV_PARTICLE;

public:
	DECLARE_RTTI(SnowParticleSystem, IParticleSystem);

	SnowParticleSystem(const char* pszImagePiece);
	virtual ~SnowParticleSystem();

	virtual void Update(float dt);
	virtual void Render();

private:
	bool Init(const char* pszImagePiece);

private:
	TV_PARTICLE m_vParticles;
	SnowEmmiter* m_pSnowEmmiter;
	VATTR_POS_UV* m_pVerts;
	ushort* m_pIndis;

	IShader* m_pShader;
	const IMAGE_PIECE* m_pImagePiece;

};
#endif // __SNOWPARTICLESYSTEM_H__
