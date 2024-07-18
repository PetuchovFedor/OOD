#pragma once
#include "IStyle.h"

class CFillStyle : public IStyle
{
public:

	std::optional<RGBAColor> GetColor() const override
	{
		return m_color;
	}

	void SetColor(const RGBAColor& rgbaColor)
	{
		m_color = rgbaColor;
	}

private:
	std::optional<RGBAColor> m_color = 0xffffff;
};