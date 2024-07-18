#pragma once
#include "Canvas.h"
#include "IMainFrameController.h"
#include "CImageFactory.h"
#include "CShapeFactory.h"

class MainFrame : public wxFrame
{
public:
    MainFrame(wxWindow* parent, CPicture* picture);
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnToolItem(wxCommandEvent& event);
    Canvas* m_canvas;
    CPicture* m_model;
    std::unique_ptr<IMainFrameController> m_controller;
    CShapeFactory m_shapesFactory;
    CImageFactory m_imageFactory;
};
