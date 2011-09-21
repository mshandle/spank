/*!
 * \file ClipRectTestCase.cpp
 * \date 2011/09/15 15:22
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include "ClipRectTestCase.h"

ClipRectTestCase::ClipRectTestCase()
:TestCase("ClipRectTestCase")
{
	//TODO:
	IUIResMgr::GetInstance().SetupDefaultButtonTextures(m_pStyle);
}

ClipRectTestCase::~ClipRectTestCase()
{
	//TODO:
}

bool ClipRectTestCase::Initialize(UIScreen* pUIScreen)
{
	////TODO:
	return true;
}

void ClipRectTestCase::Terminate()
{
	//TODO:
}

void ClipRectTestCase::Render()
{
	IRendererUI::GetInstance().BeginRender();

	IRendererUI::GetInstance().SetTexture(m_pStyle[DUS_BUTTON_DEFAULT]->pTexture);
	QUAD_VERT_POS_UV quad;

	//右上
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(100.0f, 50.0f));
	IRendererUI::GetInstance().ClipRect(quad,100.0f, 50.0f, 46.0f, 17.0f);
	IRendererUI::GetInstance().DrawRect(quad);
	//右下
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(100.0f, 100.0f));
	IRendererUI::GetInstance().ClipRect(quad,100.0f,117.0,46.0f,17.0);
	IRendererUI::GetInstance().DrawRect(quad);
	//左上
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(200.0f, 50.0f));
	IRendererUI::GetInstance().ClipRect(quad,246.0f,50.0,46.0,17.0);
	IRendererUI::GetInstance().DrawRect(quad);
	//左下
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(200.0f, 100.0f));
	IRendererUI::GetInstance().ClipRect(quad,246.0, 117.0f, 50.0f, 17.0f);
	IRendererUI::GetInstance().DrawRect(quad);
	//左半
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(100.0f, 150.0f));
	IRendererUI::GetInstance().ClipRect(quad,100.0f, 150.0f, 46.0f, 40.0);
	IRendererUI::GetInstance().DrawRect(quad);
	//右半
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(200.0f, 150.0f));
	IRendererUI::GetInstance().ClipRect(quad,246.0, 150.0f, 50.0f, 40.0f);
	IRendererUI::GetInstance().DrawRect(quad);
	//上半
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(100.0f, 200.0));
	IRendererUI::GetInstance().ClipRect(quad,100.0f, 200.0f, 100.0f, 17.0f);
	IRendererUI::GetInstance().DrawRect(quad);
	//下半
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(200.0f, 200.0));
	IRendererUI::GetInstance().ClipRect(quad,200.0f, 217.0f, 100.0f, 17.0f);
	IRendererUI::GetInstance().DrawRect(quad);
	//中间
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(100.0f, 250.0f));
	IRendererUI::GetInstance().ClipRect(quad,131.0f, 261.0f, 31.0f, 11.0f);
	IRendererUI::GetInstance().DrawRect(quad);
	//全部
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT],Vector2(100.0f, 300.0f));
	IRendererUI::GetInstance().ClipRect(quad,100.0f, 300.0f, 100.0f, 60.0f);
	IRendererUI::GetInstance().DrawRect(quad);

	IRendererUI::GetInstance().EndRender();
}
