/*!
 * \file Tile.cpp
 * \date 2011/09/21 18:05
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <Tile.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>
#include <INode.h>

const char* Tile::pszShaderFileName[] = 
{
	"trans_shader.xml",
	"Gray_shader.xml"
};

Tile::Tile(const IMAGE_PIECE* pImagePiece)
{
	m_pImagePiece = pImagePiece;
	m_bVisible= true;
	m_nWidth = pImagePiece->width;
	m_nHeight = pImagePiece->height;
	m_vColor = IMath::VEC4_ONE;
	m_pShader = IShaderMgr::GetInstance().CreateShader("trans_shader.xml");
	m_eType = NORMAL;
}

Tile::~Tile()
{
	SAFE_RELEASE(m_pShader);
}

void Tile::Update(float dt)
{
	//TODO:
}

void Tile::Render()
{
	if(!IsVisible()) return;

	INode* pNode = GetParentNode();
	if (!pNode) return;
	m_pShader->SetTexture("u_texture",m_pImagePiece->pTexture);
	if(m_eType == NORMAL)
		m_pShader->SetVector4("u_color", m_vColor);
	IRenderer2D::GetInstance().SetModelViewMatrix(pNode->GetFinalMatrix());
	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, m_nWidth, m_nHeight, m_pImagePiece, m_pShader);
}

void Tile::SetRenderType(RENDER_TYPE eType)
{
	if(eType == m_eType) return;
	SAFE_RELEASE(m_pShader);
	m_pShader = IShaderMgr::GetInstance().CreateShader(pszShaderFileName[eType]);
	if(!m_pShader)return;
	m_eType = eType;
}
void Tile::SetSize( float width, float height )
{
	m_nWidth = width;
	m_nHeight = height;
}

void Tile::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
}

void Tile::SetColor(const Vector4& vColor)
{
	//TODO:
	m_vColor = vColor;
}

float Tile::GetWidth() const
{
	return m_nWidth;
}

float Tile::GetHeight() const
{
	return m_nHeight;
}

float Tile::GetPieceWidth() const
{
	return m_pImagePiece->width;
}

float Tile::getPieceheight() const
{
	return m_pImagePiece->height;
}
bool Tile::IsVisible() const
{
	return m_bVisible;
}

INode* Tile::GetParentNode()
{
	IObject* pObject = GetParent();
	if (!pObject) return NULL;

	if (pObject->GetRtti()->IsDerived(INode::__RttiData())) return (INode*)pObject;

	return NULL;
}

