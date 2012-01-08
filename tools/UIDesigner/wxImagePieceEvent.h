/*!
 * \file wxImagePieceEvent.h
 * \date 12-09-2011 12:25:04
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __WXIMAGEPIECEEVENT_H__
#define __WXIMAGEPIECEEVENT_H__

#include <wx/event.h>
#include "UIImagePieceDocument.h"

class wxImagePieceEvent : public wxNotifyEvent
{
public:
	DECLARE_DYNAMIC_CLASS(wxImagePieceEvent);

public:
	wxImagePieceEvent(wxEventType commandType = wxEVT_NULL, int winid = 0);
	wxImagePieceEvent(const wxImagePieceEvent& event);
	virtual ~wxImagePieceEvent();

	virtual wxEvent* Clone() const;

	void SetPieceInfo(const UIImagePieceDocument::PIECE_INFO& pieceInfo);
	const UIImagePieceDocument::PIECE_INFO& GetPieceInfo() const;

private:
	UIImagePieceDocument::PIECE_INFO m_PieceInfo;

};

typedef void (wxEvtHandler::*wxImagePieceEventHandler)(wxImagePieceEvent&);

BEGIN_DECLARE_EVENT_TYPES()
	DECLARE_EVENT_TYPE(wxEVT_COMMAND_IMAGE_PIECE_CHANGED, 801)
END_DECLARE_EVENT_TYPES()

#define EVT_IMAGE_PIECE_CHANGED(id, fn) \
	DECLARE_EVENT_TABLE_ENTRY( \
	wxEVT_COMMAND_IMAGE_PIECE_CHANGED, \
	id, \
	wxID_ANY, \
	(wxObjectEventFunction)(wxEventFunction)(wxImagePieceEventHandler)&fn, \
	(wxObject*)NULL \
	),

#endif // __WXIMAGEPIECEEVENT_H__
