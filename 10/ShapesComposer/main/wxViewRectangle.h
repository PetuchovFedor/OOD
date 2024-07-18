#pragma once
#include "wxViewItem.h"

class wxViewRectangle : public wxViewItem
{
public:
    wxViewRectangle(wxWindow* parent,
        wxWindowID winId,
        IPictureItemPtr shape,
        const wxString& name,
        std::function<bool(wxViewItem*)> selectShapeCallback,
        long style = wxNO_FULL_REPAINT_ON_RESIZE
    )
        : wxViewItem(parent, winId, shape, name, selectShapeCallback, style)
    {}

    void Draw(wxDC& dc) override
    {       
        wxViewItem::Draw(dc);
        if (wxViewItem::GetSelection())
        {
            return;
        }
        auto rect = wxRect(wxPoint(0, 0), wxSize(GetSize().GetWidth() - 2,
            GetSize().GetHeight() - 2));
        wxPoint leftTop = rect.GetLeftTop();
        wxPoint rifghtTop = rect.GetRightTop();
        wxPoint leftBottom = rect.GetBottomLeft();
        wxPoint rightBottom = rect.GetBottomRight();
        dc.DrawRectangle(rect);
        /*dc.DrawLine(leftTop, rifghtTop);
        dc.DrawLine(rifghtTop, rightBottom);
        dc.DrawLine(rightBottom, leftBottom);
        dc.DrawLine(leftBottom, leftTop);*/
    }
};