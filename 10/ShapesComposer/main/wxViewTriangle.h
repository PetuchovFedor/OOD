#pragma once
#include "wxViewItem.h"

class wxViewTriangle : public wxViewItem
{
public:
    wxViewTriangle(wxWindow* parent,
        wxWindowID winId,
        IPictureItemPtr item,
        const wxString& name,
        std::function<bool(wxViewItem*)> selectItemCallback,
        long style = wxNO_FULL_REPAINT_ON_RESIZE
    )
        : wxViewItem(parent, winId, item, name, selectItemCallback, style)
    {}

    void Draw(wxDC& dc) override
    {
        wxViewItem::Draw(dc);
        auto rect = wxRect(wxPoint(0, 0), wxSize(GetSize().GetWidth() - 2,
            GetSize().GetHeight() - 2));
        wxPoint leftTop = rect.GetLeftTop();
        //wxPoint p1(leftTop.x, leftTop.y + rect.height);
        wxPoint p(leftTop.x + rect.width / 2, leftTop.y);
        dc.DrawLine(rect.GetBottomLeft(), p);
        dc.DrawLine(p, rect.GetBottomRight());
        dc.DrawLine(rect.GetBottomRight(), rect.GetBottomLeft());
    }
};