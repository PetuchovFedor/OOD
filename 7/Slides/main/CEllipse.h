#pragma once
#include "CShape.h"

class CEllipse : public CShape
{
public:
	CEllipse(const RectD& rect)
		: CShape(rect)
	{}

	void Draw(ICanvas& canvas) const final
	{
		auto frame = CShape::GetFrame();
		auto& lineStyle = CShape::GetOutlineStyle();
		auto& fillStyle = CShape::GetFillStyle();
		canvas.SetLineColor(lineStyle.GetColor().value());
		canvas.SetThickessLine(lineStyle.GetThickness());
		canvas.DrawEllipse(frame.leftTop, frame.width, frame.height);
		canvas.FillEllipse(frame.leftTop, frame.width, frame.height, 
			fillStyle.GetColor().value());
	}

	std::string GetType() const final
	{
		return "ellipse";
	}
};