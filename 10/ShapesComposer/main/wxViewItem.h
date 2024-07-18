#pragma once
#include <wx/wx.h>
#include "IPictureItem.h"
#include "ResizingMarker.h"
#include <array>
#include "IViewItemController.h"

class wxViewItem : public wxPanel, IObserver<Rect>
{
    wxDECLARE_ABSTRACT_CLASS(wxViewItem);
    wxDECLARE_EVENT_TABLE();
public:
    wxViewItem();

    wxViewItem(wxWindow* parent,
        wxWindowID winId,
        IPictureItemPtr item,
        const wxString& name,
        std::function<bool(wxViewItem*)> selectShapeCallback,
        long style = wxNO_FULL_REPAINT_ON_RESIZE
        );

    void Update(Rect const& data) override;

    virtual void Draw(wxDC& dc);

    bool GetSelection() const;

    void UnSelect();

    void Select();

    const IPictureItemPtr GetModel() const;

    ~wxViewItem()
    {

    }
private:
    void OnPaint(wxPaintEvent& event);

    void MouseEventsHandler(wxMouseEvent& evt);

    void DragAndDrop(wxMouseEvent& evt);

    void ChangeMarkerPositions(wxSizeEvent& evt);
    
    //{
    //    m_isSelect = true;
    //    m_selectShapeCallback(this);
    //    Refresh();
    //    //evt.Skip();
    //    //leftTopMarker->Show();
    //}
    //{
    //    m_isSelect = false;
    //    Refresh();
    //}

    //{
    //    return m_isSelect;
    //}

private:
    enum class ResizeMarkers
    {
        NONE,
        LEFT_TOP,
        RIGHT_TOP,
        LEFT_BOTTOM,
        RIGHT_BOTTOM
    };
    //void Resize(wxMouseEvent& evt, ResizeMarkers marker);

    IPictureItemPtr m_model;
    bool m_isSelect = false, m_isResize = false;
    wxPoint m_startPoint;
    std::array<ResizingMarker*, 4> m_resizeMarkers;
    std::unique_ptr<IViewItemController> m_controller;
    std::function<bool(wxViewItem*)> m_selectItemCallback;
};