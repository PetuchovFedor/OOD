#pragma once
#include "ResizingMarker.h"

class LeftBottomMarker : public ResizingMarker
{
public:
	LeftBottomMarker(wxWindow* parent,
		wxWindowID winId, wxPoint pos, wxSize size,
		std::function<void(wxRect)> setFrameCallback)
		: ResizingMarker(parent, winId, pos, size, setFrameCallback)
	{

	}
	void OnDragging(const wxPoint& pos) override
	{
		wxPoint delta;
		delta = pos - ResizingMarker::GetResizePos();
		wxPoint newPos = m_parent->GetPosition();
		//ResizingMarker::SetResizePos(pos);
		//SetPosition(newPos);
		newPos.x += delta.x;
		wxSize oldSize = m_parent->GetSize();
		wxSize newSize;
		newSize.SetWidth(oldSize.GetWidth() - delta.x);
		newSize.SetHeight(oldSize.GetHeight() + delta.y);
		ResizingMarker::SetResizePos(pos);
		//newPos.x -= newSize.GetWidth();
		m_parent->SetPosition(newPos);
		m_parent->SetSize(newSize);
	}
};