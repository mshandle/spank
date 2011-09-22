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
	
}

Tile::~Tile()
{
	
}

void Tile::Render()
{
	INode* pNode = GetParentNode();
	if (!pNode) return;

	static IShader* pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	pShader->SetTexture("u_texture",m_pImagePiece->pTexture);
	IRenderer2D::GetInstance().SetModelViewMatrix(pNode->GetFinalMatrix());
	pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());
	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, m_pImagePiece, pShader);
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