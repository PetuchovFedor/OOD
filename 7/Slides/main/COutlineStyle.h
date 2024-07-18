#pragma once
#include "IOutlineStyle.h"

class COutlineStyle : public IOutlineStyle
{
public:
	std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}

	void SetColor(const RGBAColor& rgbaColor) override
	{
		m_color = rgbaColor;
	}

	size_t GetThickness() const override
	{
		return m_thickness;
	}

	void SetThickess(size_t thichness) override
	{
		m_thickness = thichness;
	}

private:
	std::optional<RGBAColor> m_color = 0xffffff;
	size_t m_thickness = 2;
};