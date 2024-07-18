#pragma once
#include "IShapeStrategy.h"
#include <sstream>

class CircleStrategy : public IShapeStrategy
{
public:
	CircleStrategy(Point center, double radius)
		: m_center(center)
		, m_radius(radius)
	{
	}
	std::string GetValueParamsInString() const override
	{
		std::stringstream os;
		os << m_center.x << ' ' << m_center.y << ' ' << m_radius;
		return os.str();
	}

	std::string GetType() const override
	{
		return "circle";
	}

	void Draw(gfx::ICanvas& canvas) override
	{
		canvas.DrawEllipse(m_center.x, m_center.y, m_radius, m_radius);
	}

	void Move(Point vector) override
	{
		m_center.x += vector.x;
		m_center.y += vector.y;
	}

	////void SetCenter(Point newCenter)
	////{
	////	m_center = newCenter;
	////}

	//Point GetCenter() const
	//{
	//	return m_center;
	//}

	//double GetRadius() const
	//{
	//	return m_radius;
	//}

private:
	Point m_center;
	double m_radius;
};