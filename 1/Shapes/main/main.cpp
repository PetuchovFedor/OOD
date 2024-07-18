#include "PictureController.h"
#include "Canvas.h"
#include <iostream>

int main()
{
    shapes::Picture picture;
    Canvas canvas;
	std::string fileName;
	std::cout << "Enter output svg file name" << std::endl;
	getline(std::cin, fileName);
    PictureController controller(picture, canvas, std::cin, std::cout);
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!controller.HandleComand())
		{
			if (std::cin.eof())
			{
				
				break;
			}
			std::cout << "Unknown command!" << std::endl;
		}
	}
	canvas.Save(fileName);
}