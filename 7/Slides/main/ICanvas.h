#pragma once
#include "CommonTypes.h"
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void FillPolygon(const std::vector<PointD>& points, RGBAColor color) = 0;
	virtual void MoveTo(PointD to) = 0;
	virtual void LineTo(PointD to) = 0;
	virtual void SetThickessLine(size_t thickness) = 0;
	virtual void DrawEllipse(PointD leftTop, double width, double height) = 0;
	virtual void FillEllipse(PointD leftTop, double width, double height, RGBAColor color) = 0;

	virtual ~ICanvas() = default;
};