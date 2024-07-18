#pragma once
#include "ResizingMarker.h"

class LeftTopMarker : public ResizingMarker
{
public:
	LeftTopMarker(wxWindow* parent,
		wxWindowID winId, wxPoint pos, wxSize size,
		std::function<void(wxRect)> setFrameCallback)
		: ResizingMarker(parent, winId, pos, size, setFrameCallback)
	{

	}
	void OnDragging(const wxPoint& pos) override
	{
		wxPoint delta;
		delta = pos - ResizingMarker::GetResizePos();
		wxPoint newPos = m_parent->GetPosition() + delta;
		wxSize oldSize = m_parent->GetSize();
		wxSize newSize;
		newSize.SetWidth(oldSize.GetWidth() - delta.x);
		newSize.SetHeight(oldSize.GetHeight() - delta.y);
		ResizingMarker::SetResizePos(pos);
		m_parent->SetPosition(newPos);
		m_parent->SetSize(newSize);
	}
};