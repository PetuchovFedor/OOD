#include "Canvas.h"
#include "CCanvasController.h"
#include <algorithm>
#include "RightBottomMarker.h"
#include "wxViewEllipse.h"
#include "wxViewImage.h"
#include "wxViewRectangle.h"
#include "wxViewTriangle.h"
#include "IShape.h"
#include "CShape.h"
#include "CImage.h"

BEGIN_EVENT_TABLE(Canvas, wxPanel)
EVT_SIZE(Canvas::Resize)
EVT_MOUSE_EVENTS(Canvas::OnMouseEvents)
EVT_CHAR(Canvas::OnKeyBoardEvents)
END_EVENT_TABLE()

void Canvas::Update(PictureDataToObserver const& data)
{
	switch (data.GetOperation())
	{
	case PictureOperations::ADD_ITEM:
		{
			m_factory.CreateItem(this, data.GetItem());
			break;
		}
	case PictureOperations::DELETE_SELECT_ITEM:
		{
			m_selectedShape->Destroy();
			break;
		}
	case PictureOperations::DELETE_ITEM:
		{
			auto sh = FindWindow(data.GetItem()->GetId());
			//auto sh = FindWindowByLabel(data.GetShape()->GetId(), this);
			sh->Destroy();
			break;
		}
	case PictureOperations::CHANGE_SIZE:
		{
			if (data.GetSize()->height != GetSize().GetHeight() ||
				data.GetSize()->width != GetSize().GetWidth())
			{
				SetSize(wxSize(data.GetSize()->width, data.GetSize()->height));
			}
			break;
		}
	case PictureOperations::NONE:
		break;
	default:
		break;
	}
}

Canvas::Canvas(wxFrame* parent, CPicture* picture, wxSize size)
    : wxPanel(parent, wxID_ANY, wxDefaultPosition,
        size)
    /*: wxFrame(parent, wxID_ANY, "", wxDefaultPosition,
        size)*/
    , m_picture(picture)
{
	m_controller = std::make_unique<CCanvasController>(m_picture);
    m_picture->RegisterObserver(*this);
    SetBackgroundColour(wxColor(255, 255, 255, 1));
    SetMinSize(wxSize(300, 300));
    SetDoubleBuffered(true);
    bool a = false;
    std::function<void(wxRect)> setRectCallback = [&controller = this->m_controller](wxRect rect)
        {
			Size size;
			size.height = rect.GetHeight();
			size.width = rect.GetWidth();
			controller->SetSize(size);
        };
	m_marker = new RightBottomMarker(this, wxID_ANY,
		wxPoint(size.GetWidth() - 15, size.GetHeight() - 15), wxSize(15, 15), setRectCallback);
  /*  m_marker = new
        RightBottomMarker(this, wxID_ANY, wxPoint(size.GetWidth() - 11, size.GetHeight() - 11),
            wxSize(10, 10), setResize);*/
}


void Canvas::SelectShape(wxViewItem* shape)
{
	m_selectedShape = shape;
	//m_selectedShapes.push_back(shape);
}

void Canvas::DeleteSelectShape()
{
	m_controller->DeleteItem(m_selectedShape->GetModel()->GetId());
}

void Canvas::UnSelectShape()
{
	if (m_selectedShape)
		m_selectedShape->UnSelect();
	m_selectedShape = nullptr;
}

wxViewItem* Canvas::GetSelectShape() const
{
	return m_selectedShape;
}

void Canvas::OnKeyBoardEvents(wxKeyEvent& evt)
{
	if (evt.GetKeyCode() == WXK_DELETE)
	{
		DeleteSelectShape();
	}
	else
		evt.Skip(); // Пропускать событие, если это не нажатие кнопки "Delete"
}

void Canvas::OnMouseEvents(wxMouseEvent& evt)
{
	SetFocus();
	if (evt.LeftDown())
	{
		if (m_selectedShape)
		{
			UnSelectShape();
			evt.Skip();
		}
	}
}
void CreateViewShape(Canvas* canvas, std::shared_ptr<IShape> shape, std::function<bool(wxViewItem*)>
    selectShapeCallback)
{
	
}
void Canvas::ViewItemFactory::CreateItem(Canvas* canvas, CDocumentItem* item)
{
    wxViewItem* viewItem = nullptr;
    std::function<bool(wxViewItem*)> selectShapeCallback = [canvas](wxViewItem* sh)
        {
			if (canvas->GetSelectShape())
			{
				return false;
			}
			canvas->SelectShape(sh);
            return true;
        };

    if (item->GetImage())
    {
        CreateImage(canvas, item, selectShapeCallback);
    }
    else
    {
        CreateShape(canvas, item, selectShapeCallback);
    }
}

void Canvas::ViewItemFactory::CreateShape(Canvas* canvas, CDocumentItem* item, std::function<bool(wxViewItem*)> selectShapeCallback)
{
    auto shape = item->GetShape();
    wxViewItem* viewShape = nullptr;
    switch (shape->GetType())
    {
    case ShapeTypes::RECTANGLE:
    {
        viewShape = new wxViewRectangle(canvas, wxID_ANY, shape, shape->GetId(),
            selectShapeCallback);
        break;
    }
    case ShapeTypes::ELLIPSE:
    {
        viewShape = new wxViewEllipse(canvas, wxID_ANY, shape, shape->GetId(),
            selectShapeCallback);
        break;
    }
    case ShapeTypes::TRIANGLE:
    {
        viewShape = new wxViewTriangle(canvas, wxID_ANY, shape, shape->GetId(),
            selectShapeCallback);
        break;
    }
    default:
        break;
    }
}

void Canvas::ViewItemFactory::CreateImage(Canvas* canvas, CDocumentItem* item, std::function<bool(wxViewItem*)> selectShapeCallback)
{
    auto img = item->GetImage();
	wxViewItem* viewImg = new wxViewImage(canvas, wxID_ANY, img, img->GetId(), selectShapeCallback);
}
