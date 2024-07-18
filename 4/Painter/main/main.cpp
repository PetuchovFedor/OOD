#include <iostream>
#include "CShapeFactory.h"
#include "CDesigner.h"
#include "CPainter.h"
#include "Canvas.h"

int main()
{
	CShapeFactory factory;
	CDesigner designer(std::make_unique<CShapeFactory>(factory));
	auto maket = designer.CreateDraft(std::cin);
	CPainter painter;
	Canvas canvas;
	painter.DrawPicture(maket, canvas);
	canvas.Save("out.svg");
}
