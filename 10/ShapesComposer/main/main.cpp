// Start of wxWidgets "Hello World" Program
#include "main.h"
#include "CShape.h"

bool MyApp::OnInit()
{
    CPicture* picture = new CPicture({ 1000, 600 });
    MainFrame* frame = new MainFrame(NULL, picture);
    frame->Show(true);
    return true;
}

//bool MyApp::OnInit()
//{
//    return false;
//}
