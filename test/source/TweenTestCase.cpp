/*!
 * \file TweenTestCase.cpp
 * \date 2011/09/16 14:33
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "TweenTestCase.h"
#include <IRenderer2D.h>
#include <IResourceMgr.h>
#include <IShaderMgr.h>

#include <action/ActionSequeue.h>
#include <action/ActionLoop.h>
#include <action/ActionQuadMoveTo.h>
#include <action/ActionBackMoveTo.h>
#include <action/ActionCubicMoveTo.h>
#include <action/ActionQuartMoveTo.h>
#include <action/ActionQuintMoveTo.h>
#include <action/ActionSineMoveTo.h>
#include <action/ActionExpoMoveTo.h>
#include <action/ActionCircMoveTo.h>
#include <action/ActionElasticMoveTo.h>
#include <action/ActionBounceMoveTo.h>

#include <ui/UIButton.h>
#include <ui/UIRadioButton.h>
#include <ui/uimsg/UIMsgID.h>

#include <util/IDebugUtil.h>

TweenTestCase::TweenTestCase()
:TestCase("TweenTestCase")
{
	m_pShader = NULL;
	m_pSpriteAction = NULL;
	m_pRootNode = NULL;
	m_pUiText = NULL;

	m_nIndexTween = 0;
	m_nEffectIndex = 0;
	m_pImagePiece = NULL;
}

TweenTestCase::~TweenTestCase()
{
	for (TV_ACTIONLOOP::iterator itr = m_vActionLoop.begin(); itr != m_vActionLoop.end(); itr++)
	{
		(*itr)->DisconnectEvent(MI_ACTION_UPDATE);
		(*itr)->Release();
	}

	m_vActionLoop.clear();
}

bool TweenTestCase::Initialize(UIScreen* pUIScreen)
{
	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if (!m_pShader) return false;

	m_pImagePiece = IResourceMgr::GetInstance().FindImagePiece("test_black");
	if (!m_pImagePiece) return false;

	m_pSpriteAction = new Sprite("test_ball.xml");
	if (!m_pSpriteAction) return true;
	m_pRootNode = IResourceMgr::GetInstance().CreateRootNode();
	m_pRootNode->AttachObject(m_pSpriteAction);

	m_vActionLoop.push_back(new ActionElasticMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionElasticMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionElasticMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionBounceMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionBounceMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionBounceMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionCircMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionCircMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionCircMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionExpoMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionExpoMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionExpoMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionSineMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionSineMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionSineMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));


	m_vActionLoop.push_back(new ActionQuintMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionQuintMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionQuintMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionQuartMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionQuartMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionQuartMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionCubicMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionCubicMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionCubicMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionBackMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionBackMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionBackMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_vActionLoop.push_back(new ActionQuadMoveTo(ATT_EASE_IN, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionQuadMoveTo(ATT_EASE_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	m_vActionLoop.push_back(new ActionQuadMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));

	m_pUiText = new UITextView(pUIScreen, Vector2(10.0f, 340.0f), "ActionElasticMoveTo");

	ActionSequeue* pActionSequeue = new ActionSequeue();
	pActionSequeue->AddAction(m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]);
	m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]->IncRef();
	ActionLoop* pActionLoop = new ActionLoop(pActionSequeue);
	m_pRootNode->RunAction(pActionLoop);
	
	UIButton* pBtRrvButton = new UIButton(pUIScreen, Vector2(10.0f, 10.0f), "Prv");
	pBtRrvButton->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&TweenTestCase::OnBtnPrevClicked);

	UIButton* pBtNextButton = new UIButton(pUIScreen, Vector2(10.0f, 60.0f), "Next");
	pBtNextButton->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&TweenTestCase::OnBtnNextClicked);

	UIRadioButton* pBtInButton = new UIRadioButton(pUIScreen, Vector2(200.0f, 10.0f), "Ease In");
	pBtInButton->SetCheck(true);
	pBtInButton->ConnectEvent(UMI_CHECKED, this, (MSG_CALLBACK)&TweenTestCase::OnBtnEaseInClicked);

	UIRadioButton* pBtOutButton = new UIRadioButton(pUIScreen, Vector2(200.0f, 60.0f), "Ease Out");
	pBtOutButton->ConnectEvent(UMI_CHECKED, this, (MSG_CALLBACK)&TweenTestCase::OnBtnEaseOutClicked);

	UIRadioButton* pBtInOutButton = new UIRadioButton(pUIScreen, Vector2(200.0f, 110.0f), "Ease In & Out");
	pBtInOutButton->ConnectEvent(UMI_CHECKED, this, (MSG_CALLBACK)&TweenTestCase::OnEASEInOutButton);

	return true;
}

void TweenTestCase::Terminate()
{
	SAFE_RELEASE(m_pRootNode);
	SAFE_DELETE(m_pSpriteAction);
	SAFE_RELEASE(m_pShader);
}

void TweenTestCase::Update(float dt)
{
	// update actions
	m_pRootNode->UpdateAction(dt);
	// update objects
	m_pRootNode->UpdateObjects(dt);
	// update matrix
	m_pRootNode->UpdateMatrix(dt);
}

void TweenTestCase::Render()
{
	IRenderer2D::GetInstance().SetModelViewMatrix(IMath::MAT4X4_IDENTITY);
	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());
	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, 700.0f, 3.0f, m_pImagePiece, m_pShader);

	m_pRootNode->RenderObjects();
}

bool TweenTestCase::OnBtnPrevClicked(IMsgBase* pMsg)
{
	if(((int)m_nIndexTween - 1) >= 0)
	{
		m_nIndexTween--;
		UpdateTween();
	}

	return true;
}

bool TweenTestCase::OnBtnNextClicked(IMsgBase* pMsg)
{
	if((m_nIndexTween + 1) < (m_vActionLoop.size() / TWEEN_TYPE_SIZE))
	{
		m_nIndexTween++;
		UpdateTween();
	}

	return true;
}

bool TweenTestCase::OnBtnEaseInClicked(IMsgBase* pMsg)
{ 
	if(m_nEffectIndex == 0) return true;
	m_nEffectIndex = 0;
	UpdateTween();

	return true;
}

bool TweenTestCase::OnBtnEaseOutClicked(IMsgBase* pMsg)
{
	if(m_nEffectIndex == 1) return true;
	m_nEffectIndex = 1;
	UpdateTween();
	return true;
}

bool TweenTestCase::OnEASEInOutButton(IMsgBase* pMsg)
{
	if(m_nEffectIndex == 2) return true;
	m_nEffectIndex = 2;
	UpdateTween();

	return true;
}

void TweenTestCase::UpdateTween()
{
	static const char* s_pszText[] =
	{
		"ActionElasticMoveTo",
		"ActionBounceMoveTo",
		"ActionCircMoveTo",
		"ActionExpoMoveTo",
		"ActionSineMoveTo",
		"ActionQuintMoveTo",
		"ActionQuartMoveTo",
		"ActionCubicMoveTo",
		"ActionBackMoveTo",
		"ActionQuadMoveTo"
	};

	m_pUiText->SetText(s_pszText[m_nIndexTween]);
	ActionSequeue* pActionSequeue = new ActionSequeue();
	pActionSequeue->AddAction(m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]);
	m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]->IncRef();
	ActionLoop* pActionLoop = new ActionLoop(pActionSequeue);
	m_pRootNode->RunAction(pActionLoop);
}
