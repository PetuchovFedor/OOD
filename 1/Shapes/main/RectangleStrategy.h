#pragma once
#include "IShapeStrategy.h"
#include <sstream>

class RectangleStrategy : public IShapeStrategy
{
public:
	RectangleStrategy(Point leftTop, double width, double height)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
	{
	}

	std::string GetType() const override
	{
		return "rectangle";
	}

	std::string GetValueParamsInString() const override
	{
		std::stringstream os;
		os << m_leftTop.x << ' ' << m_leftTop.y << ' ' << m_width << ' ' << m_height;
		return os.str();
	}

	void Draw(gfx::ICanvas& canvas) override
	{
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(static_cast<int>(m_leftTop.x + m_width), m_leftTop.y);
		canvas.LineTo(static_cast<int>(m_leftTop.x + m_width), static_cast<int>(m_leftTop.y + m_height));
		canvas.LineTo(m_leftTop.x, static_cast<int>(m_leftTop.y + m_height));
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

	void Move(Point vector) override
	{
		m_leftTop.x += vector.x;
		m_leftTop.y += vector.y;
	}

	//void SetLeftTop(Point newLeftTop);

	//double GetWidth() const
	//{
	//	return m_width;
	//}

	//Point GetLeftTop() const
	//{
	//	return m_leftTop;
	//}

	//double GetHeight() const
	//{
	//	return m_height;
	//}

private:
	Point m_leftTop;
	double m_width, m_height;
};