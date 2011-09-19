/*!
 * \file TweenTestCase.cpp
 * \date 2011/09/16 14:33
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "TweenTestCase.h"
#include <ICore.h>
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
TweenTestCase::TweenTestCase()
:TestCase("TweenTestCase")
{	
	m_pSpriteAction = NULL;
	m_pActionNode = NULL;
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

	pActionFregment->AddAction(new ActionElasticMoveTo(ATT_EASE_IN_OUT, Vector3(-350.0f, 0.0f ,0.0f), Vector3(350.0f , 0.0f, 0.0f), 6.0f));
	ActionSequeue* pActionSequeue = new ActionSequeue();
	pActionSequeue->AddAction(pActionFregment);

	ActionLoop* pActionLoop = new ActionLoop(pActionSequeue);
	m_pActionNode->RunAction(pActionLoop);
	return true;
}

void TweenTestCase::Terminate()
{
	ICore::GetInstance().GetRootNode()->RemoveChildNode(m_pActionNode);
	m_pActionNode = NULL;
	SAFE_DELETE(m_pSpriteAction);
}
