#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	//у эллипса ширина и высота описанного прямоугольника
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Point from, Point to) = 0;
	virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
	virtual ~ICanvas() = default;
};