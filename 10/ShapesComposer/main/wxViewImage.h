#pragma once
#include "wxViewItem.h"
#include "IImage.h"

class wxViewImage : public wxViewItem
{
public:
    wxViewImage(wxWindow* parent,
        wxWindowID winId,
        std::shared_ptr<IImage> img,
        const wxString& name,
        std::function<bool(wxViewItem*)> selectItemCallback,
        long style = wxNO_FULL_REPAINT_ON_RESIZE
    )
        : wxViewItem(parent, winId, img, name, selectItemCallback, style)
    {
       /* auto string = img.
        if (img->GetPath().)*/
        //wxInitAllImageHandlers();
        //m_img.SetSize(wxViewItem::GetSize());
        wxImage::AddHandler(new wxPNGHandler);
        m_img.LoadFile(wxString(img->GetPath()), wxBITMAP_TYPE_PNG);
        m_img.Rescale(img->GetFrame().size.width, img->GetFrame().size.height);
    }

    void Draw(wxDC& dc) override
    {

        wxViewItem::Draw(dc);
        if (m_img.GetSize() != GetSize())
        {
            m_img.Rescale(GetSize().GetWidth(), GetSize().GetHeight());
        }
        wxBitmap bitmap(m_img);
        dc.DrawBitmap(bitmap, wxPoint(0, 0));
    }
private:
    wxImage m_img;
};