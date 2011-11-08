/*!
 * \file UITestCase.cpp
 * \date 8-26-2011 17:39:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UITestCase.h"
#include <ui/UITextView.h>
#include <ui/UIButton.h>
#include <ui/UICheckButton.h>
#include <ui/UIRadioButton.h>
#include <ui/UISliderBar.h>
#include <ui/uimsg/MsgClick.h>
#include <ui/uimsg/MsgCheck.h>
#include <ui/uimsg/MsgSlider.h>
#include <ui/uimsg/UIMsgID.h>
#include <util/IDebugUtil.h>

UITestCase::UITestCase()
:TestCase("UITestCase")
{
	// TODO: 
}

UITestCase::~UITestCase()
{
	// TODO: 
}

bool UITestCase::Initialize(UIScreen* pUIScreen)
{
	static const char* s_pszText = "This program will allow you to generate\n"
								   "bitmap fonts from TrueType fonts.\n\n"
								   "The application generates both image\n"
								   "files and character descriptions that\n"
								   "can be read by a game for easy\n"
								   "rendering of fonts.";

	int nID = 1;

// 	{
// 		UITextView* pTextView = new UITextView(pUIScreen, s_pszText);
// 		pTextView->SetID(nID++);
// 		pTextView->SetPosition(Vector2(80.0f, 50.0f));
// 	}

	{
		/*Test show a normal button*/
		UIButton* pButton = new UIButton(pUIScreen);
		pButton->SetID(nID++);
		pButton->SetPosition(Vector2(10.0f, 10.0f));
		pButton->SetText("Button1");
		pButton->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&UITestCase::OnButtonClicked);
	}

	{
		/* Test, show a list of Check button. you can set a callback funtion for the each CheckButton */
		for (int i = 0; i < 3; ++i)
		{
			UICheckButton* pUICheck = new UICheckButton(pUIScreen);
			pUICheck->SetID(nID++);
			pUICheck->SetPosition(Vector2(10.0f, 100.0f+i*50.0f));
			pUICheck->SetText("Check");
			pUICheck->ConnectEvent(UMI_CHECKED, this, (MSG_CALLBACK)&UITestCase::OnCheckButtonChecked);
		}
	}

	{
		/*Test, show a list Radio button, you should get a RadioGroup first*/
		for (int i = 0; i < 3; ++i)
		{
			UIRadioButton* pUIRadio = new UIRadioButton(pUIScreen);
			pUIRadio->SetID(nID++);
			pUIRadio->SetPosition(Vector2(210.0f, 100.0f+i*50.0f));
			pUIRadio->SetText("Radio");
			pUIRadio->ConnectEvent(UMI_CHECKED, this, (MSG_CALLBACK)&UITestCase::OnRadioButtonChecked);
		}
	}

	{
		/*Test, show a Slider, you should set a maskTexture.at last*/
		UISliderBar* pSlider = new UISliderBar(pUIScreen);
		pSlider->SetID(nID++);
		pSlider->SetPosition(Vector2(10.0f, 250.0f));
		pSlider->SetSliderRange(0, 10);
		pSlider->ConnectEvent(UMI_SLIDER, this, (MSG_CALLBACK)&UITestCase::OnSlider);
	}

	return true;
}

void UITestCase::Terminate()
{
	// TODO: 
}

void UITestCase::Update(float dt)
{
	// TODO: 
}

void UITestCase::Render()
{
	// TODO: 
}

bool UITestCase::OnButtonClicked(IMsgBase* pMsg)
{
	MsgClick* pMsgClick = (MsgClick*)pMsg;
	LOGD("button (%d) clicked", pMsgClick->GetSenderID());
	return true;
}

bool UITestCase::OnCheckButtonChecked(IMsgBase* pMsg)
{
	MsgCheck* pMsgCheck = (MsgCheck*)pMsg;
	LOGD("check button (%d) checked: (%d)", pMsgCheck->GetSenderID(), (int)pMsgCheck->IsChecked());
	return true;
}

bool UITestCase::OnRadioButtonChecked(IMsgBase* pMsg)
{
	MsgCheck* pMsgCheck = (MsgCheck*)pMsg;
	LOGD("radio button (%d) checked: (%d)", pMsgCheck->GetSenderID(), (int)pMsgCheck->IsChecked());
	return true;
}

bool UITestCase::OnSlider(IMsgBase* pMsg)
{
	MsgSlider* pMsgSlider = (MsgSlider*)pMsg;
	LOGD("slider bar (%d) pos:%d", pMsgSlider->GetSenderID(), pMsgSlider->GetPosition());
	return true;
}
