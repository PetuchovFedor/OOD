#pragma once
#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color)
		: m_color(color)
	{}

	virtual void Draw(ICanvas& canvas) = 0;

	Color GetColor() const
	{
		return m_color;
	}
private:
	Color m_color;
};