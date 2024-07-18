#pragma once
#include "IStyle.h"

class CGroupFillStyle : public IStyle
{
public:
	CGroupFillStyle(StyleEnumerator enumerator)
		: m_enumerator(move(enumerator))
	{}

	std::optional<RGBAColor> GetColor() const override
	{
		std::optional<RGBAColor> result = std::nullopt;
		bool isFirstElem = true;
		FuncWorksWithStyles func = [&result, &isFirstElem](IStyle& style)
			{
				if (isFirstElem)
				{
					result = style.GetColor();
					isFirstElem = false;
				}
				else if (result != style.GetColor())
				{
					result = std::nullopt;
				}
			};
		m_enumerator(func);
		return result;
	}

	void SetColor(const RGBAColor& rgbaColor) override
	{
		FuncWorksWithStyles func = [&rgbaColor](IStyle& style)
			{
				style.SetColor(rgbaColor);
			};
		m_enumerator(func);
	}

private:
	StyleEnumerator m_enumerator;

};
