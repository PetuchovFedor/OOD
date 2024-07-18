#include "MainFrame.h"
#include "CShape.h"
#include "CMainFrameController.h"
#include "wxViewTriangle.h"
#include "wxViewRectangle.h"
#include "wxViewEllipse.h"
#include "GenerateRandomString.h"

namespace
{
    const int ID_TRIANGLE = 100;
    const int ID_RECTANGLE = 101;
    const int ID_ELLIPSE = 102;
    const int ID_IMAGE = 103;
    const int ID_UNDO = 104;
    const int ID_REDO = 105;
    const int ID_DELETE = 106;

    const Size DEFAULT_SIZE = { 100, 100 };
}


MainFrame::MainFrame(wxWindow* parent, CPicture* picture)
    : wxFrame(parent,
        wxID_ANY, 
       wxT("Shapes Compositer"),
        wxDefaultPosition,
        wxSize(1200, 600))
    , m_model(picture)
{
    m_controller = std::make_unique<CMainFrameController>(picture);
    auto sizer = new wxBoxSizer(wxVERTICAL);
    SetBackgroundColour(wxColor(0xa8e4a0));
    wxImage::AddHandler(new wxPNGHandler);
    wxMenu* menuFile = new wxMenu;
    menuFile->AppendSeparator();
    menuFile->Append(wxID_EXIT);
    
    wxMenu* menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    
    wxMenuBar* menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    menuBar->Append(menuHelp, "&Help");
    SetMenuBar(menuBar);

    wxToolBar* toolbar = new wxToolBar(this, wxID_ANY);
    toolbar->SetToolBitmapSize(wxSize(40, 40));
    wxBitmap triangle(wxT("icons/triangle.png"), wxBITMAP_TYPE_PNG);
    wxBitmap rectangle(wxT("icons/rectangle.png"), wxBITMAP_TYPE_PNG);
    wxBitmap ellipse(wxT("icons/ellipse.png"), wxBITMAP_TYPE_PNG);
    wxBitmap undo(wxT("icons/undo.png"), wxBITMAP_TYPE_PNG);
    wxBitmap redo(wxT("icons/redo.png"), wxBITMAP_TYPE_PNG);
    wxBitmap cross(wxT("icons/cross.png"), wxBITMAP_TYPE_PNG);
    wxBitmap img(wxT("icons./picture.png"), wxBITMAP_TYPE_PNG);
    toolbar->AddTool(ID_TRIANGLE, wxT("triangle"), triangle);
    toolbar->AddTool(ID_RECTANGLE, wxT("rectangle"), rectangle);
    toolbar->AddTool(ID_ELLIPSE, wxT("ellipse"), ellipse);
    toolbar->AddTool(ID_IMAGE, wxT("picture"), img);
    toolbar->AddSeparator();
    toolbar->AddSeparator();
    toolbar->AddTool(ID_UNDO, wxT("undo"), undo);
    toolbar->AddTool(ID_REDO, wxT("redo"), redo);
    toolbar->AddTool(ID_DELETE, wxT("delete"), cross);
    toolbar->Realize();

    //SetToolBar(toolbar);
    CreateStatusBar();
    SetStatusText("Welcome to wxWidgets!");
    m_canvas = new Canvas((wxFrame*)this, m_model, 
        wxSize(m_model->GetSize().width, m_model->GetSize().height));

    sizer->Add(toolbar, 0, wxALIGN_CENTER | wxALL, FromDIP(10));
    sizer->Add(m_canvas, 1, wxSHAPED|wxLEFT, FromDIP(30));
    SetSizer(sizer);
    toolbar->Bind(wxEVT_TOOL, &MainFrame::OnToolItem, this);
    //Bind(wxEVT_MENU, &MainFrame::OnHello, this, ID_Hello);
    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}

void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}

void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a wxWidgets Hello World example",
        "About Hello World", wxOK | wxICON_INFORMATION);
}

void MainFrame::OnToolItem(wxCommandEvent& event)
{
    int id = event.GetId();
    Point center;
    center.x = m_canvas->GetSize().GetWidth() / 2;
    center.y = m_canvas->GetSize().GetHeight() / 2;
    switch (id)
    {
    case ID_TRIANGLE:
    {
        IShapePtr item = m_shapesFactory.CreateShape(GenerateRandomString(), 
            ShapeTypes::TRIANGLE, Rect(center, DEFAULT_SIZE));
        m_controller->AddShape(item);
        break;
    }

    case ID_RECTANGLE:
    {
        IShapePtr item = m_shapesFactory.CreateShape(GenerateRandomString(),
            ShapeTypes::RECTANGLE, Rect(center, DEFAULT_SIZE));
        m_controller->AddShape(item);
        break;
    }
    case ID_ELLIPSE:
    {
        IShapePtr item = m_shapesFactory.CreateShape(GenerateRandomString(),
            ShapeTypes::ELLIPSE, Rect(center, DEFAULT_SIZE));
        m_controller->AddShape(item);
        break;
    }
    case ID_IMAGE:
    {
        wxFileDialog openFileDialog(this, "Open Image", "", "", 
            "Image files (*.png)|*.png", wxFD_OPEN | wxFD_FILE_MUST_EXIST);

        if (openFileDialog.ShowModal() == wxID_CANCEL) {
            return;
        }

        wxString filePath = openFileDialog.GetPath();

        IImagePtr item = m_imageFactory.CreateImage(GenerateRandomString(),
            filePath.wc_str(), Rect(center, DEFAULT_SIZE));
        m_controller->AddImage(item);
        break;
    }
    case ID_UNDO:
    {
        //std::wstring str = std::to_wstring(m_model.GetShapesCount());
        //wxLogMessage("Undo");
        m_controller->Undo();
        break;
    }
    case ID_REDO:
    {
        m_controller->Redo();
        break;
    }
    case ID_DELETE:
    {
        m_canvas->DeleteSelectShape();
        break;
    }
    default:
        break;
    }
}
