/*!
 * \file wxImagePieceEvent.cpp
 * \date 12-09-2011 12:25:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "wxImagePieceEvent.h"

DEFINE_EVENT_TYPE(wxEVT_COMMAND_IMAGE_PIECE_CHANGED)
IMPLEMENT_DYNAMIC_CLASS(wxImagePieceEvent, wxNotifyEvent)

wxImagePieceEvent::wxImagePieceEvent(wxEventType commandType /*= wxEVT_NULL*/, int winid /*= 0*/)
:wxNotifyEvent(commandType, winid)
{
	m_PieceInfo.strId.clear();
	m_PieceInfo.nImageId = 0;
	m_PieceInfo.pieceRect = wxRect(0, 0, 0, 0);
}

wxImagePieceEvent::wxImagePieceEvent(const wxImagePieceEvent& event)
:wxNotifyEvent(event)
{
	m_PieceInfo = event.m_PieceInfo;
}

wxImagePieceEvent::~wxImagePieceEvent()
{
	// TODO: 
}

wxEvent* wxImagePieceEvent::Clone() const
{
	return new wxImagePieceEvent(*this);
}

void wxImagePieceEvent::SetPieceInfo(const UIImagePieceDocument::PIECE_INFO& pieceInfo)
{
	m_PieceInfo = pieceInfo;
}

const UIImagePieceDocument::PIECE_INFO& wxImagePieceEvent::GetPieceInfo() const
{
	return m_PieceInfo;
}
