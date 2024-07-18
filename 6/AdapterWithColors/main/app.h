#pragma once
#include "modern_graphics_lib_pro.h"
#include "shape_drawing_lib.h"
#include "ModernGraphicsLibAdapter.h"

namespace app
{
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter);
	void PaintPictureOnCanvas();

	void PaintPictureOnModernGraphicsRenderer()
	{
		modern_graphics_lib_pro::CModernGraphicsRenderer renderer(std::cout);
		//(void)&renderer;
		ModernGraphicsLibAdapter adapter(renderer);
		shape_drawing_lib::CCanvasPainter painter(adapter);
		PaintPicture(painter);
	}
	void PaintPicture(shape_drawing_lib::CCanvasPainter& painter)
	{
		using namespace shape_drawing_lib;
		//9d81ba
		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 10322362);
		//2271b3
		CRectangle rectangle({ 30, 40 }, 18, 24, 2257331);
		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib::CCanvas simpleCanvas;
		shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

}