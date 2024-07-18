#include <iostream>
#include "CSlideController.h"
#include "CSvgCanvas.h"

int main()
{
	std::string fileName;
	std::cout << "Enter output svg file name" << std::endl;
	getline(std::cin, fileName);
	CSvgCanvas canvas;
	CSlideController controller(std::cin, std::cout, canvas);
	while (!std::cin.eof() && !std::cin.fail())
	{
		if (!controller.HandleCommand())
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
