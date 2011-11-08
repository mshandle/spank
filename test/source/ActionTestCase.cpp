/*!
 * \file ActionTestCase.cpp
 * \date 27-08-2011 04:51:45
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ActionTestCase.h"
#include <IResourceMgr.h>
#include <action/ActionMoveTo.h>
#include <action/ActionRotateTo.h>
#include <action/ActionScaleTo.h>
#include <action/ActionSequeue.h>
#include <action/ActionLoop.h>

ActionTestCase::ActionTestCase()
:TestCase("ActionTestCase")
{
	m_pSprite = NULL;
	m_pRootNode = NULL;
}

ActionTestCase::~ActionTestCase()
{
	// TODO: 
}

bool ActionTestCase::Initialize(UIScreen* pUIScreen)
{
	m_pSprite = new Sprite("test_sprite.xml");
	if (!m_pSprite) return true;

	m_pRootNode = IResourceMgr::GetInstance().CreateRootNode();
	m_pRootNode->AttachObject(m_pSprite);

	ActionSequeue* pActionFregment = new ActionSequeue();
	pActionFregment->AddAction(new ActionMoveTo(Vector3(-200.0f, 0.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 3.0f));
	pActionFregment->AddAction(new ActionRotateTo(Vector3(0.0f, 0.0f, 1.0f), 0.0f, IMath::F_PI2, 3.0f));
	pActionFregment->AddAction(new ActionScaleTo(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.5f, 0.5f, 0.5f), 1.5f));

	ActionSequeue* pActionSequeue = new ActionSequeue();
	pActionSequeue->AddAction(pActionFregment);
	pActionSequeue->AddAction(pActionFregment->CloneInverse());
	ActionLoop * pActionLoop = new ActionLoop(pActionSequeue);

	m_pRootNode->RunAction(pActionLoop);

	return true;
}

void ActionTestCase::Terminate()
{
	SAFE_RELEASE(m_pRootNode);
	SAFE_DELETE(m_pSprite);
}

void ActionTestCase::Update(float dt)
{
	// update actions
	m_pRootNode->UpdateAction(dt);
	// update objects
	m_pRootNode->UpdateObjects(dt);
	// update matrix
	m_pRootNode->UpdateMatrix(dt);
}

void ActionTestCase::Render()
{
	m_pRootNode->RenderObjects();
}
