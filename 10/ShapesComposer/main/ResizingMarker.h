#pragma once
#include <wx/wx.h>
#include <functional>
#include "CommonTypes.h"

class ResizingMarker : public wxPanel
{
	wxDECLARE_ABSTRACT_CLASS(wxViewItem);
	wxDECLARE_EVENT_TABLE();
public:
	ResizingMarker();

	ResizingMarker(wxWindow* parent,
		wxWindowID winId, wxPoint pos, wxSize size, 
		std::function<void(wxRect)> setFrameCallback);

	void OnPaint(wxPaintEvent& event);

	void ResizeParent(wxMouseEvent& evt);
	
	virtual void OnDragging(const wxPoint& pos) = 0;

	void SetResizePos(const wxPoint& p)
	{
		m_startPoint = p;
	}

	wxPoint GetResizePos() const
	{
		return m_startPoint;
	}

	~ResizingMarker()
	{
		
	}
private:
	std::function<void(wxRect)> m_setFrameCallback;
	wxPoint m_startPoint;
};