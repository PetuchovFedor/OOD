#include "ResizingMarker.h"

BEGIN_EVENT_TABLE(ResizingMarker, wxPanel)
EVT_PAINT(ResizingMarker::OnPaint)
EVT_MOUSE_EVENTS(ResizingMarker::ResizeParent)
END_EVENT_TABLE()
IMPLEMENT_ABSTRACT_CLASS(ResizingMarker, wxPanel)

ResizingMarker::ResizingMarker(wxWindow* parent, wxWindowID winId, wxPoint pos, wxSize size, 
	std::function<void(wxRect)> setFrameCallback)
	: wxPanel(parent, winId, pos, size, wxBORDER_NONE)
	, m_setFrameCallback(move(setFrameCallback))
{
	SetDoubleBuffered(true);
	//SetBackgroundColour(wxColour(255, 255, 0, 0.7));
}

ResizingMarker::ResizingMarker()
{
	//m_parent;
}

void ResizingMarker::OnPaint(wxPaintEvent& event)
{
	wxPaintDC dc(this);
	wxRect rect(wxPoint(0, 0), GetSize());
	dc.SetPen(wxPen(wxColour(255, 255, 0)));
	dc.SetBrush(wxBrush(wxColour(255, 255, 0)));
	dc.DrawEllipse(rect);
	//dc.Fi
	//dc.DrawEllipse(rect);
}

void ResizingMarker::ResizeParent(wxMouseEvent& evt)
{
	if (evt.Dragging())
	{
		OnDragging(m_parent->GetPosition() + evt.GetPosition());
		m_parent->Refresh();
	}
	else if (evt.LeftDown())
	{
		//m_setResize(true);
		SetResizePos(m_parent->GetPosition() + evt.GetPosition());
	}
	else if (evt.LeftUp())
	{
		/*Rect frame;
		frame.leftTop.x = GetPosition().x;
		frame.leftTop.y = GetPosition().y;
		frame.size.height = GetSize().GetHeight();
		frame.size.width = GetSize().GetWidth();*/
		m_setFrameCallback(m_parent->GetRect());
		//m_setResize(false);
	}
}
