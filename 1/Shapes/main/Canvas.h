#pragma once
#include "ICanvas.h"
#include "Point.h"
#include <sstream>

class Canvas : public gfx::ICanvas
{
public:
	void MoveTo(double x, double y) override;
	void SetColor(const gfx::Color& color) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void DrawText(double left, double top, double fontSize, const std::string& text) override;
	void Save(const std::string& fileName);
private:
	gfx::Color m_colorOfPen;
	Point m_drawingPos;
	std::stringstream m_output;
};