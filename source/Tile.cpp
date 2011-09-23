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

Tile::Tile(const IMAGE_PIECE* pImagePiece, const Vector3& Pos/* = IMATH::VERTOR3_ZERO*/)
{
	m_pImagePiece = pImagePiece;
	m_vPos = Pos;
	m_bVisual= true;
	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
}

Tile::~Tile()
{
	//TODO:
	SAFE_RELEASE(m_pShader);

}
void Tile::Render()
{
	INode* pNode = GetParentNode();
	if (!pNode) return;
	if(!m_bVisual) return;
	m_pShader->SetTexture("u_texture",m_pImagePiece->pTexture);
	IRenderer2D::GetInstance().SetModelViewMatrix(pNode->GetFinalMatrix());
	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());
	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, m_pImagePiece, m_pShader);
	
}

void Tile::Update(float dt)
{
	//TODO:
}

INode* Tile::GetParentNode()
{
	IObject* pObject = GetParent();
	if (!pObject) return NULL;

	if (pObject->GetRtti()->IsDerived(INode::__RttiData())) return (INode*)pObject;

	return NULL;
}

void Tile::SetVisual(bool bVisual)
{
	m_bVisual = bVisual;
}