/*!
 * \file Sprite.cpp
 * \date 30-07-2011 16:18:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <Sprite.h>
#include <util/IFileUtil.h>
#include <IShaderMgr.h>
#include <ITextureMgr.h>
#include <IRenderer2D.h>
#include <IResourceMgr.h>
#include <INode.h>
#include <tinyxml-2.6.2/tinyxml.h>

Sprite::Sprite(const char* pszSpriteFile)
{
	m_pShader = NULL;
	m_nNumFrames = 0;

	m_fCurrTime = 0.0f;
	m_nCurrIndex = 0;
	m_nLoop = 0;
	m_nCurrLoop = 0;

	m_pSpriteFrames = NULL;
	m_bRunning = false;

	m_vColor = IMath::VEC4_ONE;

	m_bOK = LoadSpriteFromFile(pszSpriteFile);
}

Sprite::~Sprite()
{
	SAFE_RELEASE(m_pShader);
	SAFE_DELETE_ARRAY(m_pSpriteFrames);
}

void Sprite::Update(float dt)
{
	if (!IsRunning()) return;

	m_fCurrTime += dt;

	if (m_fCurrTime > m_pSpriteFrames[m_nCurrIndex].fFrameTime)
	{
		m_fCurrTime -= m_pSpriteFrames[m_nCurrIndex].fFrameTime;
		m_nCurrIndex = (m_nCurrIndex + 1) % m_nNumFrames;

		if (m_nCurrIndex == 0)	// one loop ended
		{
			if (m_nCurrLoop > 0) --m_nCurrLoop;
			if (m_nLoop > 0 && m_nCurrLoop == 0) Stop();
		}
	}
}

void Sprite::Render()
{
	INode* pNode = GetParentNode();
	if (!pNode) return;

	m_pShader->SetTexture("u_texture", m_pSpriteFrames[m_nCurrIndex].pImagePiece->pTexture);
 	m_pShader->SetVector4("u_color", m_vColor);

	IRenderer2D::GetInstance().SetModelViewMatrix(pNode->GetFinalMatrix());
	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, m_pSpriteFrames[m_nCurrIndex].pImagePiece, m_pShader);
}

void Sprite::SetLoop(int nLoop)
{
	m_nLoop = nLoop;
	Reset();
}

int Sprite::GetLoop() const
{
	return m_nLoop;
}

int Sprite::GetCurrentLoop() const
{
	return m_nCurrLoop;
}

void Sprite::Start()
{
	SetRunning(true);
}

void Sprite::Stop()
{
	SetRunning(false);
	Reset();
}

void Sprite::Pause()
{
	SetRunning(false);
}

void Sprite::Restart()
{
	Reset();
	SetRunning(true);
}

void Sprite::Reset()
{
	m_fCurrTime = 0.0f;
	m_nCurrIndex = 0;
	m_nCurrLoop = m_nLoop;
	m_bRunning = false;
}

bool Sprite::SetRunning(bool bRunning)
{
	bool difference = (m_bRunning != bRunning);
	m_bRunning = bRunning;
	return difference;
}

bool Sprite::IsRunning() const
{
	return m_bRunning;
}

void Sprite::SetColor(const Vector4& material)
{
	m_vColor = material;
}

void Sprite::SetColor(float r, float g, float b, float a)
{
	m_vColor.x = r;
	m_vColor.y = g;
	m_vColor.z = b;
	m_vColor.w = a;
}

const Vector4& Sprite::GetColor() const
{
	return m_vColor;
}

bool Sprite::LoadSpriteFromFile(const char* pszSpriteFile)
{
	StreamReader* pReader = IFileUtil::GetInstance().LoadFile(pszSpriteFile);
	if (!pReader) return false;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);

	if (doc.Error()) return false;

	// parse the xml files
	TiXmlElement* pElmSprite = doc.RootElement();
	if (!pElmSprite) return false;

	const char* pszShader = NULL;
	pszShader = pElmSprite->Attribute("shader");
	if (!pszShader) return false;

	pElmSprite->Attribute("num_frames", &m_nNumFrames);
	if (m_nNumFrames <= 0) return false;

	m_pSpriteFrames = new SPRITE_FRAME[m_nNumFrames];
	if (!m_pSpriteFrames) return false;

	TiXmlElement* pElmFrame = pElmSprite->FirstChildElement("frame");
	for (int i = 0; i < m_nNumFrames; ++i)
	{
		if (!pElmFrame) return false;

		const char* pszID = pElmFrame->Attribute("id");
		if (!pszID) return false;

		int nTime = 0;
		if (!pElmFrame->Attribute("time", &nTime)) return false;

		m_pSpriteFrames[i].pImagePiece = IResourceMgr::GetInstance().FindImagePiece(pszID);
		if (!m_pSpriteFrames[i].pImagePiece) return false;
		m_pSpriteFrames[i].fFrameTime = nTime / 1000.0f;

		pElmFrame = pElmFrame->NextSiblingElement("frame");
	}

	m_pShader = IShaderMgr::GetInstance().CreateShader(pszShader);
	if (!m_pShader) return false;

	return true;
}

INode* Sprite::GetParentNode()
{
	IObject* pObject = GetParent();
	if (!pObject) return NULL;

	if (pObject->GetRtti()->IsDerived(INode::__RttiData())) return (INode*)pObject;

	return NULL;
}
