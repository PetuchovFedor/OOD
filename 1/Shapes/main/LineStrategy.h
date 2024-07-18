#pragma once
#include "IShapeStrategy.h"
#include <sstream>

class LineStrategy : public IShapeStrategy
{
public:
	LineStrategy(Point begin, Point end)
		: m_beginPoint(begin)
		, m_endPoint(end)
	{
	}

	std::string GetType() const override
	{
		return "line";
	}

	void Move(Point vector) override
	{
		m_beginPoint.x += vector.x;
		m_beginPoint.y += vector.y;
		m_endPoint.x += vector.x;
		m_endPoint.y += vector.y;
	}

	void Draw(gfx::ICanvas& canvas) override
	{
		canvas.MoveTo(m_beginPoint.x, m_beginPoint.y);
		canvas.LineTo(m_endPoint.x, m_endPoint.y);
	}

	std::string GetValueParamsInString() const override
	{
		std::stringstream os;
		os << m_beginPoint.x << ' ' << m_beginPoint.y << ' ' << m_endPoint.x
			<< ' ' << m_endPoint.y;
		return os.str();
	}

	//void SetBeginPoint(Point newPoint)
	//{
	//	m_beginPoint = newPoint;
	//}

	/*void SetEndPoint(Point newPoint)
	{
		m_endPoint = newPoint;
	}

	Point GetBeginPoint() const
	{
		return m_beginPoint;
	}

	Point GetEndPoint() const
	{
		return m_endPoint;
	}*/

private:
	Point m_beginPoint, m_endPoint;
};