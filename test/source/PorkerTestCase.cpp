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
	m_pNode = NULL;
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
	m_pNode = ICore::GetInstance().GetRootNode()->CreateChildNode();
	m_pNode->AttachObject(m_pTile);

	UIButton* pButtonNormal = new UIButton(pUIScreen);
	pButtonNormal->SetText("Normal");
	pButtonNormal->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&PorkerTestCase::OnNormalButtonClick);

	UIButton* pButtonGray = new UIButton(pUIScreen);
	pButtonGray->SetText("Gray");
	pButtonGray->SetPosition(0.0f, 60.0f);
	pButtonGray->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)& PorkerTestCase::OnGrayButtonClick);
	return true;
}

void PorkerTestCase::Terminate()
{
	SAFE_RELEASE(m_pShader);
	ICore::GetInstance().GetRootNode()->RemoveChildNode(m_pNode);
}

void PorkerTestCase::Render()
{
	
}

bool PorkerTestCase::OnNormalButtonClick(IMsgBase* pMsg)
{
	m_pTile->SetRenderType(Tile::NORMAL);
	return true;
}

bool PorkerTestCase::OnGrayButtonClick(IMsgBase* pMsg)
{
	m_pTile->SetRenderType(Tile::GRAY);
	return true;
}