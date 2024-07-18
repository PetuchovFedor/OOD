#pragma once
#include "IShapeStrategy.h"
#include <sstream>

class TriangleStrategy : public IShapeStrategy
{
public:
	TriangleStrategy(Point vertex1, Point vertex2, Point vertex3)
		: m_vertex1(vertex1)
		, m_vertex2(vertex2)
		, m_vertex3(vertex3)
	{
	}

	std::string GetType() const override
	{
		return "triangle";
	}

	std::string GetValueParamsInString() const override
	{
		std::stringstream os;
		os << m_vertex1.x << ' ' << m_vertex1.y << ' ' << m_vertex2.x << ' ' <<
			m_vertex2.y << ' ' << m_vertex3.x << ' ' << m_vertex3.y;
		return os.str();
	}

	void Draw(gfx::ICanvas& canvas) override
	{
		canvas.MoveTo(m_vertex1.x, m_vertex1.y);
		canvas.LineTo(m_vertex2.x, m_vertex2.y);
		canvas.LineTo(m_vertex3.x, m_vertex3.y);
		canvas.LineTo(m_vertex1.x, m_vertex1.y);
	}

	void Move(Point vector) override
	{
		m_vertex1.x += vector.x;
		m_vertex1.y += vector.y;
		m_vertex2.x += vector.x;
		m_vertex2.y += vector.y;
		m_vertex3.x += vector.x;
		m_vertex3.y += vector.y;
	}

	//void SetVertex1(Point newVertex);

	//void SetVertex2(Point newVertex);

	//void SetVertex3(Point newVertex);

	/*Point GetVertex1() const
	{
		return m_vertex1;
	}

	Point GetVertex2() const
	{
		return m_vertex2;
	}

	Point GetVertex3() const
	{
		return m_vertex3;
	}*/

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};