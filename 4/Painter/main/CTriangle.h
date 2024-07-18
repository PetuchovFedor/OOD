#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle(Color color, Point vert1, Point vert2, Point vert3)
		: CShape(color)
		, m_vertex1(vert1)
		, m_vertex2(vert2)
		, m_vertex3(vert3)
	{}

	Point GetVertex1() const
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
	}

	void Draw(ICanvas& canvas) override
	{
		canvas.SetColor(CShape::GetColor());
		canvas.DrawLine(m_vertex1, m_vertex2);
		canvas.DrawLine(m_vertex2, m_vertex3);
		canvas.DrawLine(m_vertex3, m_vertex1);
	}

private:
	Point m_vertex1, m_vertex2, m_vertex3;
};