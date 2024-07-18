#pragma once
#include "CPicture.h"
#include <vector>
#include "ICanvasController.h"
#include "wxViewItem.h"

class Canvas : public wxPanel, public IObserver<PictureDataToObserver>
{
    DECLARE_EVENT_TABLE()
public:
    Canvas(wxFrame* parent, CPicture* picture, wxSize size);

    void Update(PictureDataToObserver const& data) override;
    
    void SelectShape(wxViewItem* shape);

    void DeleteSelectShape();

    void UnSelectShape();

    wxViewItem* GetSelectShape() const;
private:

    void OnKeyBoardEvents(wxKeyEvent& evt);

    void OnMouseEvents(wxMouseEvent& evt);

    void Resize(wxSizeEvent& event) {
        auto size = event.GetSize();
        m_marker->SetPosition(wxPoint( size.GetWidth() - 15, size.GetHeight() - 15));
        Refresh();
    }
protected:

    class ViewItemFactory
    {
    public:
        void CreateItem(Canvas* canvas, CDocumentItem* item);
    private:
        void CreateShape(Canvas* canvas, CDocumentItem* item,
            std::function<bool(wxViewItem*)> selectShapeCallback);
        void CreateImage(Canvas* canvas, CDocumentItem* item,
            std::function<bool(wxViewItem*)> selectShapeCallback);
    };

private:
    CPicture* m_picture;
    wxViewItem* m_selectedShape;
    ViewItemFactory m_factory;
    ResizingMarker* m_marker;
    std::unique_ptr<ICanvasController> m_controller;
};