#pragma once
#include "IShape.h"

class CShape : public IShape
{
public:
	CShape(ShapeTypes type, const Rect& rect, const std::string& id)
		: m_type(type)
		, m_rect(rect)
		, m_id(id)
	{}

	std::string GetId() const  override
	{
		return m_id;
	}
	Rect GetFrame() const override
	{
		return m_rect;
	}

	void SetFrame(const Rect& frame) override
	{
		m_rect = frame;
	}

	ShapeTypes GetType() const override
	{
		return m_type;
	}

	Point GetPosition() const override
	{
		return m_rect.leftTop;
	}

	void SetPosition(Point leftTop) override
	{
		m_rect.leftTop = leftTop;
	}

protected:

	Rect GetChangedData() const override
	{
		return m_rect;
	}

private:
	ShapeTypes m_type;
	std::string m_id;
	Rect m_rect;
};