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
#include <IResourceMgr.h>
PorkerTestCase::PorkerTestCase()
:TestCase("PorkerTestCase")
{
	m_pBackGroundImagePiece = NULL;
	m_pShader = NULL;
}

PorkerTestCase::~PorkerTestCase()
{

}

bool PorkerTestCase::Initialize( UIScreen* pUIScreen )
{

	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if(!m_pShader) return false;
	m_pBackGroundImagePiece = IResourceMgr::GetInstance().FindImagePiece("backgorund");
	if(!m_pBackGroundImagePiece) return false;
	return true;
}

void PorkerTestCase::Terminate()
{

}

void PorkerTestCase::Render()
{
	

	IRenderer2D::GetInstance().BeginRender();
	m_pShader->SetTexture("u_texture",m_pBackGroundImagePiece->pTexture);
	m_pShader->SetMatrix4x4("u_matModelViewProj",IRenderer2D::GetInstance().GetFinalMatrixTranspose());
	IRenderer2D::GetInstance().DrawRect(0, 0, (float)ScreenUtil::GetInstance().GetScreenWidth(), (float)ScreenUtil::GetInstance().GetScreenHeight() ,m_pBackGroundImagePiece, m_pShader);
	IRenderer2D::GetInstance().EndRender();
}
