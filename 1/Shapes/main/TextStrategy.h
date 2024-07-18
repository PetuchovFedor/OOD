#pragma once
#include "IShapeStrategy.h"
#include <sstream>
class TextStrategy : public IShapeStrategy
{
public:
	TextStrategy(Point leftTop, double fontSize, const std::string& text)
		: m_leftTop(leftTop)
		, m_fontSize(fontSize)
		, m_text(text)
	{
	}

	std::string GetType() const override
	{
		return "text";
	}

	std::string GetValueParamsInString() const override
	{
		std::stringstream os;
		os << m_leftTop.x << ' ' << m_leftTop.y << ' ' << m_fontSize << ' ' << m_text;
		return os.str();
	}

	void Draw(gfx::ICanvas& canvas) override
	{
		canvas.DrawText(m_leftTop.x, m_leftTop.y, m_fontSize, m_text);
	}

	void Move(Point vector) override
	{
		m_leftTop.x += vector.x;
		m_leftTop.y += vector.y;
	}

	//void SetLeftTop(Point newLeftTop);

	/*Point GetLeftTop() const
	{
		return m_leftTop;
	}

	double GetFontSize() const
	{
		return m_fontSize;
	}

	std::string GetText() const
	{
		return m_text;
	}*/

private:
	Point m_leftTop;
	double m_fontSize;
	std::string m_text;
};