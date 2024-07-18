#pragma warning(disable : 4996)
#include "wxViewItem.h"
#include "LeftTopMarker.h"
#include "RightTopMarker.h"
#include "RightBottomMarker.h"
#include "LeftBottomMarker.h"
#include "CViewItemController.h"

BEGIN_EVENT_TABLE(wxViewItem, wxPanel)
EVT_PAINT(wxViewItem::OnPaint)
EVT_MOUSE_EVENTS(wxViewItem::MouseEventsHandler)
EVT_SIZE(wxViewItem::ChangeMarkerPositions)
END_EVENT_TABLE()

IMPLEMENT_ABSTRACT_CLASS(wxViewItem, wxPanel)


wxViewItem::wxViewItem()
{
	m_model = nullptr;
}

wxViewItem::wxViewItem(wxWindow* parent, wxWindowID winId, IPictureItemPtr item, 
	const wxString& name, std::function<bool(wxViewItem*)> selectShapeCallback, long style)
	: wxPanel(parent, winId, wxPoint(item->GetPosition().x, item->GetPosition().y), wxSize(
		item->GetFrame().size.width + 2, item->GetFrame().size.height + 2),
		wxNO_FULL_REPAINT_ON_RESIZE, 
		name)
	, m_model(move(item))
	, m_selectItemCallback(move(selectShapeCallback))
{
	m_model->RegisterObserver(*this);
	std::function<void(wxRect)> setFrameCallback = [&controller = this->m_controller](wxRect frame) 
	{
		Rect rect;
		rect.leftTop.x = frame.GetLeftTop().x;
		rect.leftTop.y = frame.GetLeftTop().y;
		rect.size.width = frame.GetWidth();
		rect.size.height = frame.GetHeight();
		controller->SetFrame(rect);
	};
	m_controller = std::make_unique<CViewItemController>(m_model);
	SetDoubleBuffered(true);
	m_resizeMarkers[0] = new
		LeftTopMarker(this, wxID_ANY, wxPoint(0, 0), wxSize(10, 10), setFrameCallback);
	m_resizeMarkers[1] = new
		RightTopMarker(this, wxID_ANY, wxPoint(m_model->GetFrame().size.width - 10, 0),
			wxSize(10, 10), setFrameCallback);
	m_resizeMarkers[2] = new 
		RightBottomMarker(this, wxID_ANY,
			wxPoint(m_model->GetFrame().size.width - 10, m_model->GetFrame().size.height - 10), wxSize(10, 10),
			setFrameCallback);
	m_resizeMarkers[3] = new
		LeftBottomMarker(this, wxID_ANY, wxPoint(0, m_model->GetFrame().size.height - 10), wxSize(10, 10),
			setFrameCallback);
}

void wxViewItem::Update(Rect const& data)
{
	if (data.leftTop.x != GetPosition().x || data.leftTop.y != GetPosition().y)		
	{
		SetPosition(wxPoint(data.leftTop.x, data.leftTop.y));
	}
	if (data.size.width != GetSize().GetWidth() || data.size.height !=
		GetSize().GetHeight())
	{
		SetSize(wxSize(data.size.width, data.size.height));
	}
}

//bool wxViewShape::Create(wxWindow* parent,
//	wxWindowID winId,
//	IShapePtr shape,
//	const wxString& label,
//	std::function<void(wxViewShape*)> selectShapeCallback,
//	long style,
//	const wxValidator&
//	const wxString& name")
//{
//	if (!wxPanel::Create(parent, winId, wxPoint(shape->GetPosition().x, shape->GetPosition().y), 
//		wxSize(shape->GetFrame().width, shape->GetFrame().height), style))
//		return false;
//	//SetBackgroundColour(wxColor(255, 0, 255));
//	//SetBorderColor
//	return true;
//}


void wxViewItem::OnPaint(wxPaintEvent&)
{
	wxPaintDC dc(this);
	Draw(dc);
}

const IPictureItemPtr wxViewItem::GetModel() const
{
	return m_model;
}

void wxViewItem::Draw(wxDC& dc)
{
	if (m_isSelect)
	{
		dc.SetPen(wxPen(wxColour(255, 255, 150), 5, wxSOLID));
		wxSize size(GetSize().GetWidth() - 2, GetSize().GetHeight() - 2);
		dc.DrawRectangle(wxRect(wxPoint(0, 0), size));
		for (auto marker : m_resizeMarkers)
		{
			if (marker)
				marker->Show();
		}
	}
	else
	{
		for (auto marker : m_resizeMarkers)
		{
			if (marker)
				marker->Hide();
		}
	}
	dc.SetPen(wxPen(wxColour(0, 0, 0), 1));
	
}

void wxViewItem::MouseEventsHandler(wxMouseEvent& evt)
{

	if (evt.LeftDClick())
	{
		Select();
	}
	else if (m_isSelect)
		DragAndDrop(evt);
}

void wxViewItem::DragAndDrop(wxMouseEvent& evt)
{
	if (evt.Dragging())
	{
		if (m_startPoint.x == 0 && m_startPoint.y == 0)
			return;
		wxPoint delta; 
		
		delta = evt.GetPosition() + GetPosition() - m_startPoint;
		m_startPoint = evt.GetPosition() + GetPosition();

		wxPoint newPos;
		newPos.x = GetPosition().x + delta.x;
		newPos.y = GetPosition().y + delta.y;
		if ((newPos.x <= 0 || newPos.x + GetSize().GetWidth() >= 
			m_parent->GetSize().GetWidth())
			|| (newPos.y <= 0 || newPos.y + GetSize().GetHeight() >= 
				m_parent->GetSize().GetHeight()))
		{
			return;
		}
		SetPosition(newPos);
	}
	else if (evt.LeftDown())
	{
		m_startPoint = evt.GetPosition() + GetPosition();
		
	}
	else if (evt.LeftUp())
	{
		m_startPoint = { 0, 0 };
		m_controller->SetPosition({ GetPosition().x, GetPosition().y });
	}
}

void wxViewItem::ChangeMarkerPositions(wxSizeEvent& evt)
{
	//auto w = GetSize();
	auto newSize = evt.GetSize();
	m_resizeMarkers[1]->SetPosition({ newSize.GetWidth() - 10, 0 });
	m_resizeMarkers[2]->SetPosition(
		{ newSize.GetWidth() - 10, newSize.GetHeight() - 10 });
	m_resizeMarkers[3]->SetPosition({ 0, newSize.GetHeight() - 10 });
}

void wxViewItem::Select()
{
	if (m_selectItemCallback(this))
	{
		m_isSelect = true;
		Refresh();
	}
}

void wxViewItem::UnSelect()
{
	
	m_isSelect = false;
	Refresh();
}

bool wxViewItem::GetSelection() const
{
	return m_isSelect;
}