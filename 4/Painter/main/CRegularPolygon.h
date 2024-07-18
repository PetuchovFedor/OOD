#pragma once
#include "CShape.h"
#include <vector>
#include <valarray>
#include <cmath>

const double PI = std::atan(1.0) * 4;

class CRegularPolygon : public CShape
{
public:
	CRegularPolygon(Color color, unsigned vertexCount,
		Point center, double radius)
		: CShape(color)
		, m_vertexCount(vertexCount)
		, m_center(center)
		, m_radius(radius)
	{}

	unsigned GetVertexCount() const
	{
		return m_vertexCount;
	}

	Point GetCenter() const
	{
		return m_center;
	}

	double GetRadius() const
	{
		return m_radius;
	}

	std::vector<Point> GetVertexes() const
	{
		std::vector<Point> vertexes;
		double theta = PI / 2;
		double dTheta = 2 * PI / m_vertexCount;
		for (size_t i = 0; i < m_vertexCount; i++)
		{
			theta += dTheta;
			Point vertex;
			vertex.x = m_center.x + m_radius * cos(theta);
			vertex.y = m_center.y + m_radius * sin(theta);
			vertexes.push_back(vertex);
		}
		return vertexes;
	}

	void Draw(ICanvas& canvas) override
	{
		auto vertexes = GetVertexes();
		canvas.SetColor(CShape::GetColor());
		for (size_t i = 0; i < (m_vertexCount - 1); i++)
		{
			canvas.DrawLine(vertexes[i], vertexes[i + 1]);
		}
		canvas.DrawLine(vertexes.back(), vertexes.front());
	}

private:
	unsigned m_vertexCount;
	Point m_center;
	double m_radius;
};