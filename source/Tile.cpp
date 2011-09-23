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

Tile::Tile(const IMAGE_PIECE* pImagePiece)
{
	m_pImagePiece = pImagePiece;
	m_bVisible= true;

	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
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

	IRenderer2D::GetInstance().SetModelViewMatrix(pNode->GetFinalMatrix());
	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, m_pImagePiece, m_pShader);
}

void Tile::SetVisible(bool bVisible)
{
	m_bVisible = bVisible;
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
