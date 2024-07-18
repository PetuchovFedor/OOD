#include <iostream>
#include <string>
#include "app.h"
#include <sstream>
int main()
{
    std::stringstream stream;
    modern_graphics_lib::CModernGraphicsRenderer renderer(stream);
    std::cout << stream.str();
    std::cout << "Should we use new API (y)?";
    std::string userInput;
    if (getline(std::cin, userInput) && (userInput == "y" || userInput == "Y"))
    {
        app::PaintPictureOnModernGraphicsRenderer();
    }
    else
    {
        app::PaintPictureOnCanvas();
    }
}
