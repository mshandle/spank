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
#include <math.h>
#include <util/IDebugUtil.h>
#include <ui/uimsg/UIMsgID.h>
TweenTestCase::TweenTestCase()
:TestCase("TweenTestCase")
{	
	m_pSpriteAction = NULL;
	m_pActionNode = NULL;
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

	ActionSequeue* pActionFregment = new ActionSequeue();
	pActionFregment->AddAction(new ActionElasticMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
	ActionSequeue* pActionSequeue = new ActionSequeue();
	pActionSequeue->AddAction(pActionFregment);

	ActionLoop* pActionLoop = new ActionLoop(pActionSequeue);
	m_pActionNode->RunAction(pActionLoop);
	
	UIButton* pBtRrvButton = new UIButton(pUIScreen);
	pBtRrvButton->SetPosition(Vector2(10.0f, 10.0f));
	pBtRrvButton->SetText("Prv");
	pBtRrvButton->ConnectEvent(UMI_CLICKED, this, CAST_MSG_CALLBACK(&TweenTestCase::OnPrvButton));

	UIButton* pBtNextButton = new UIButton(pUIScreen);
	pBtNextButton->SetPosition(Vector2(10.f, 60.0f));
	pBtNextButton->SetText("Next");
	pBtNextButton->ConnectEvent(UMI_CLICKED, this, CAST_MSG_CALLBACK(& TweenTestCase::OnNextButton));
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
	LOGE("OnPrvButton Click");
	if(((int)m_nIndexTween - 1) >= 0)
		m_nIndexTween --;
	LOGE("%d",m_nIndexTween);

}

void TweenTestCase::OnNextButton( IMsgBase* pMsg )
{
	const int MAX_SIZE = 6;
	if((m_nIndexTween + 1) <= MAX_SIZE)
		m_nIndexTween++;
	LOGE("OnNextButton Click");
	LOGE("%d",m_nIndexTween);
}

void TweenTestCase::ConnectAction( uint nIndex )
{
	ICore::GetInstance().GetRootNode()->RemoveChildNode(m_pActionNode);
	ActionSequeue* pActionFregment = new ActionSequeue();
	switch(nIndex)
	{
	case 1:	
		{
			pActionFregment->AddAction(new ActionElasticMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 3.0f));
			break;
		}
	case 2:
		{
			break;
			//TODO:
		}
	}

	ActionSequeue* pActionSequeue = new ActionSequeue();
	pActionSequeue->AddAction(pActionFregment);
	ActionLoop* pActionLoop = new ActionLoop(pActionSequeue);
	m_pActionNode->RunAction(pActionLoop);
}
