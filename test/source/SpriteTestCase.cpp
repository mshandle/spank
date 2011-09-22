/*!
 * \file SpriteTestCase.cpp
 * \date 27-08-2011 04:53:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SpriteTestCase.h"
#include <ICore.h>
#include <ui/UIButton.h>
#include <ui/UISliderBar.h>
#include <ui/uimsg/UIMsgID.h>
#include <ui/uimsg/MsgSlider.h>

SpriteTestCase::SpriteTestCase()
:TestCase("SpriteTestCase")
{
	m_pSprite = NULL;
	m_pSpriteNode = NULL;
}

SpriteTestCase::~SpriteTestCase()
{
	// TODO: 
}

bool SpriteTestCase::Initialize(UIScreen* pUIScreen)
{
	m_pSpriteNode = ICore::GetInstance().GetRootNode()->CreateChildNode();
	m_pSprite = new Sprite("test_sprite.xml");
	if (!m_pSprite) return false;

	m_pSpriteNode->AttachObject(m_pSprite);

	UIButton* pButtonStart = new UIButton(pUIScreen, Vector2(10.0f, 100.0f), "Start");
	pButtonStart->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&SpriteTestCase::OnBtnStartClicked);
	UIButton* pButtonPause = new UIButton(pUIScreen, Vector2(110.0f, 100.0f), "Pause");
	pButtonPause->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&SpriteTestCase::OnBtnPauseClicked);
	UIButton* pButtonStop = new UIButton(pUIScreen, Vector2(210.0f, 100.0f), "Stop");
	pButtonStop->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&SpriteTestCase::OnBtnStopClicked);
	UIButton* pButtonRestart = new UIButton(pUIScreen, Vector2(310.0f, 100.0f), "Restart");
	pButtonRestart->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&SpriteTestCase::OnBtnRestartClicked);

	UISliderBar* pSlider = new UISliderBar(pUIScreen, Vector2(30.0f, 150.0f));
	pSlider->SetSliderRange(0, 100);
	pSlider->SetCurrentPos(100);
	pSlider->ConnectEvent(UMI_SLIDER, this, (MSG_CALLBACK)&SpriteTestCase::OnSlider);

	return true;
}

void SpriteTestCase::Terminate()
{
	ICore::GetInstance().GetRootNode()->RemoveChildNode(m_pSpriteNode);
	m_pSpriteNode = NULL;
	SAFE_DELETE(m_pSprite);
}

bool SpriteTestCase::OnBtnStartClicked(IMsgBase* pMsg)
{
	m_pSprite->Start();
	return true;
}

bool SpriteTestCase::OnBtnPauseClicked(IMsgBase* pMsg)
{
	m_pSprite->Pause();
	return true;
}

bool SpriteTestCase::OnBtnStopClicked(IMsgBase* pMsg)
{
	m_pSprite->Stop();
	return true;
}

bool SpriteTestCase::OnBtnRestartClicked(IMsgBase* pMsg)
{
	m_pSprite->Restart();
	return true;
}

bool SpriteTestCase::OnSlider(IMsgBase* pMsg)
{
	MsgSlider* pMsgSlider = (MsgSlider*)pMsg;
	int nPos = pMsgSlider->GetPosition();
	float fAlpha = nPos / 100.0f;
	m_pSprite->SetColor(1.0f, 1.0f, 1.0f, fAlpha);
	return true;
}
