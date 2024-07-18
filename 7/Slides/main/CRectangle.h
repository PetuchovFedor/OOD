#pragma once
#include "CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD& rect)
		: CShape(rect)
	{}

	void Draw(ICanvas& canvas) const final
	{
		auto frame = CShape::GetFrame();
		auto& lineStyle = CShape::GetOutlineStyle();
		auto& fillStyle = CShape::GetFillStyle();
		canvas.SetLineColor(lineStyle.GetColor().value());
		canvas.SetThickessLine(lineStyle.GetThickness());
		canvas.MoveTo(frame.leftTop);
		std::vector<PointD> points;
		points.push_back(frame.leftTop);
		points.push_back({ frame.leftTop.x + frame.width, frame.leftTop.y });
		points.push_back({ frame.leftTop.x + frame.width, frame.leftTop.y + frame.height });
		points.push_back({ frame.leftTop.x, frame.leftTop.y + frame.height });
		canvas.LineTo(points[1]);
		canvas.LineTo(points[2]);
		canvas.LineTo(points[3]);
		canvas.LineTo(points[0]);
		canvas.FillPolygon(points, fillStyle.GetColor().value());
	}

	std::string GetType() const final
	{
		return "rectangle";
	}
};