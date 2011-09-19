/*!
 * \file TweenTestCase.cpp
 * \date 2011/09/16 14:33
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "TweenTestCase.h"
#include <ICore.h>
#include <IRenderer2D.h>
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
#include <math.h>
#include <util/IDebugUtil.h>
#include <ui/uimsg/UIMsgID.h>
TweenTestCase::TweenTestCase()
:TestCase("TweenTestCase")
{	
	m_pSpriteAction = NULL;
	m_pActionNode = NULL;
	m_pActionSequeue = NULL;
	m_pActionLoop = NULL;
	m_nIndexTween = 0;
	m_nEffectIndex = 0;
}

TweenTestCase::~TweenTestCase()
{
	 // TODO: 
}

bool TweenTestCase::Initialize(UIScreen* pUIScreen)
{
	

	m_pSpriteAction = new Sprite("test_ball.xml");
	if (!m_pSpriteAction) return true;
	m_pActionNode = ICore::GetInstance().GetRootNode()->CreateChildNode();
	m_pActionNode->AttachObject(m_pSpriteAction);


	m_pActionSequeue = new ActionSequeue();
	

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

	
	m_pActionSequeue->AddAction(m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]);
	m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]->IncRef();
	m_pActionLoop = new ActionLoop(m_pActionSequeue);
	m_pActionNode->RunAction(m_pActionLoop);
	
	
	UIButton* pBtRrvButton = new UIButton(pUIScreen);
	pBtRrvButton->SetPosition(Vector2(10.0f, 10.0f));
	pBtRrvButton->SetText("Prv");
	pBtRrvButton->ConnectEvent(UMI_CLICKED, this, CAST_MSG_CALLBACK(&TweenTestCase::OnPrvButton));

	UIButton* pBtNextButton = new UIButton(pUIScreen);
	pBtNextButton->SetPosition(Vector2(10.f, 60.0f));
	pBtNextButton->SetText("Next");
	pBtNextButton->ConnectEvent(UMI_CLICKED, this, CAST_MSG_CALLBACK(&TweenTestCase::OnNextButton));

	UIRadioButton* pBtInButton = new UIRadioButton(pUIScreen);
	pBtInButton->SetPosition(Vector2(200.0f, 10.0f));
	pBtInButton->SetText("EASEIN");
	pBtInButton->SetCheck(true);
	pBtInButton->ConnectEvent(UMI_CHECKED, this, CAST_MSG_CALLBACK(&TweenTestCase::OnEASEInButton));

	UIRadioButton* pBtOutButton = new UIRadioButton(pUIScreen);
	pBtOutButton->SetPosition(Vector2(200.0f, 60.0f));
	pBtOutButton->SetText("EASEOut");
	pBtOutButton->ConnectEvent(UMI_CHECKED, this, CAST_MSG_CALLBACK(&TweenTestCase::OnEASEInOutButton));

	UIRadioButton* pBtInOutButton = new UIRadioButton(pUIScreen);
	pBtInOutButton->SetPosition(Vector2(200.0f, 110.0f));
	pBtInOutButton->SetText("EASEInOut");
	pBtInOutButton->ConnectEvent(UMI_CHECKED, this, CAST_MSG_CALLBACK(&TweenTestCase::OnEASEInOutButton));


	return true;
	

}

void TweenTestCase::Terminate()
{
	ICore::GetInstance().GetRootNode()->RemoveChildNode(m_pActionNode);
	m_pActionNode = NULL;
	SAFE_DELETE(m_pSpriteAction);
}

void TweenTestCase::Render()
{

}

void TweenTestCase::OnPrvButton( IMsgBase* pMsg )
{
	LOGD("OnPrvButton Click");
	if(((int)m_nIndexTween - 1) >= 0)
	{
		m_nIndexTween --;
		UpdateTween();
	}

}

void TweenTestCase::OnNextButton( IMsgBase* pMsg )
{
	
	if((m_nIndexTween + 1) <= m_vActionLoop.size())
	{
		m_nIndexTween++;
		UpdateTween();
		
	}
	LOGD("OnNextButton Click");
}

void TweenTestCase::OnEASEInButton( IMsgBase* pMsg )
{
	if(m_nEffectIndex == 0) return;
	m_nEffectIndex = 0;
	UpdateTween();
	LOGD("OnEASEInButton Click");
}

void TweenTestCase::OnEASEOutButton( IMsgBase* pMsg )
{
	if(m_nEffectIndex == 1) return;
	m_nEffectIndex = 1;
	UpdateTween();
	LOGD("OnEASEOutButton Click");
}

void TweenTestCase::OnEASEInOutButton( IMsgBase* pMsg )
{
	if(m_nEffectIndex == 2)return;
	m_nEffectIndex = 2;
	UpdateTween();
	LOGD("OnEASEInOutButton Click");
}

void TweenTestCase::UpdateTween()
{
	m_pActionSequeue = new ActionSequeue();
	m_pActionSequeue->AddAction(m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]);
	m_vActionLoop[m_nIndexTween * TWEEN_TYPE_SIZE + m_nEffectIndex]->IncRef();
	m_pActionLoop = new ActionLoop(m_pActionSequeue);
	m_pActionNode->RunAction(m_pActionLoop);
}

