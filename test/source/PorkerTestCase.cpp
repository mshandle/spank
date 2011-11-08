/*!
 * \file PorkerTestCase
 * \date 2011/9/20 20:41
 *
 *
 * \author wbaoqing(wbaoqing@gmail.com)
 */
#include "PorkerTestCase.h"
#include <ITextureMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>
#include <util/ScreenUtil.h>
#include <ui/UIButton.h>
#include <ui/uimsg/UIMsgID.h>
#include <IResourceMgr.h>
#include <Tile.h>
#include <ICore.h>

PorkerTestCase::PorkerTestCase()
:TestCase("PorkerTestCase")
{
	m_pBackGroundImagePiece = NULL;
	m_pShader = NULL;
	m_pTile = NULL;
	m_pRootNode = NULL;
}

PorkerTestCase::~PorkerTestCase()
{
	// TODO: 
}

bool PorkerTestCase::Initialize(UIScreen* pUIScreen)
{
	m_pBackGroundImagePiece = IResourceMgr::GetInstance().FindImagePiece("backgorund");
	if(!m_pBackGroundImagePiece) return false;
	
	m_pTile = new Tile(m_pBackGroundImagePiece);
	m_pRootNode = IResourceMgr::GetInstance().CreateRootNode();
	m_pRootNode->AttachObject(m_pTile);

	UIButton* pButtonNormal = new UIButton(pUIScreen);
	pButtonNormal->SetText("Normal");
	pButtonNormal->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&PorkerTestCase::OnNormalButtonClicked);

	UIButton* pButtonGray = new UIButton(pUIScreen);
	pButtonGray->SetText("Gray");
	pButtonGray->SetPosition(0.0f, 60.0f);
	pButtonGray->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)& PorkerTestCase::OnGrayButtonClicked);
	return true;
}

void PorkerTestCase::Terminate()
{
	SAFE_RELEASE(m_pShader);
	SAFE_RELEASE(m_pRootNode);
}

void PorkerTestCase::Update(float dt)
{
	// update actions
	m_pRootNode->UpdateAction(dt);
	// update objects
	m_pRootNode->UpdateObjects(dt);
	// update matrix
	m_pRootNode->UpdateMatrix(dt);
}

void PorkerTestCase::Render()
{
	m_pRootNode->RenderObjects();
}

bool PorkerTestCase::OnNormalButtonClicked(IMsgBase* pMsg)
{
	m_pTile->SetRenderType(Tile::NORMAL);
	return true;
}

bool PorkerTestCase::OnGrayButtonClicked(IMsgBase* pMsg)
{
	m_pTile->SetRenderType(Tile::GRAY);
	return true;
}