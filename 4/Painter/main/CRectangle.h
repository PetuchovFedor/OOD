#pragma once
#include "CShape.h"

class CRectangle : public CShape
{
public:
	CRectangle(Color color, Point leftTop, Point rightBot)
		: CShape(color)
		, m_leftTop(leftTop)
		, m_rightBottom(rightBot)
	{}

	Point GetLeltTop() const
	{
		return m_leftTop;
	}

	Point GetRightBottom() const
	{
		return m_rightBottom;
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(CShape::GetColor());
		Point rightTop(m_rightBottom.x, m_leftTop.y);
		Point leftBot(m_leftTop.x, m_rightBottom.y);
		canvas.DrawLine(m_leftTop, rightTop);
		canvas.DrawLine(rightTop, m_rightBottom);
		canvas.DrawLine(m_rightBottom, leftBot);
		canvas.DrawLine(leftBot, m_leftTop);
	}
private:
	Point m_leftTop, m_rightBottom;
};