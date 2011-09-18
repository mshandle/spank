/*!
 * \file ParticleTestCase.cpp
 * \date 27-08-2011 05:24:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ParticleTestCase.h"

ParticleTestCase::ParticleTestCase()
:TestCase("ParticleTestCase")
{
	m_pSnow = NULL;
}

ParticleTestCase::~ParticleTestCase()
{
	// TODO: 
}

bool ParticleTestCase::Initialize(UIScreen* pUIScreen)
{
	m_pSnow = new SnowParticleSystem("test_snow");
	if (!m_pSnow || !m_pSnow->IsOK()) return false;

	return true;
}

void ParticleTestCase::Terminate()
{
	SAFE_DELETE(m_pSnow);
}

void ParticleTestCase::Update(float dt)
{
	m_pSnow->Update(dt);
}

void ParticleTestCase::Render()
{
	m_pSnow->Render();
}
