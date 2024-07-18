#pragma once
#include "ICanvas.h"
#include "Point.h"
#include <sstream>

class Canvas : public ICanvas
{
public:
	void SetColor(Color color) override;
	void DrawLine(Point from, Point to) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void Save(const std::string& fileName);
private:
	std::string ToHex(Color color);
	Color m_colorOfPen;
	std::stringstream m_output;
};