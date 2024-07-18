#pragma once
#include "wxViewItem.h"

class wxViewEllipse : public wxViewItem
{
public:
    wxViewEllipse(wxWindow* parent,
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
        dc.SetBrush(wxNullBrush);
        auto rect = wxRect(wxPoint(0, 0), wxSize(GetSize().GetWidth() - 2,
            GetSize().GetHeight() - 2 ));
        dc.DrawEllipse(rect);
    }
};