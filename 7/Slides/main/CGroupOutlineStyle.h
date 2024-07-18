#pragma once
#include "IOutlineStyle.h"
#include <functional>

class CGroupOutlineStyle : public IOutlineStyle
{
public:
	CGroupOutlineStyle(OutlineStyleEnumerator enumerator)
		: m_enumerator(move(enumerator))
	{}

	std::optional<RGBAColor> GetColor() const override
	{
		std::optional<RGBAColor> result = std::nullopt;
		bool isFirstElem = true;
		FuncWorksWithOutlineStyles func = [&result, &isFirstElem](IOutlineStyle& style)
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
		FuncWorksWithOutlineStyles func = [&rgbaColor](IOutlineStyle& style)
			{
				style.SetColor(rgbaColor);
			};
		m_enumerator(func);

	}

	size_t GetThickness() const override
	{
		size_t result = 0;
		bool isFirstElem = true;
		FuncWorksWithOutlineStyles func = [&result, &isFirstElem](IOutlineStyle& style)
			{
				if (isFirstElem)
				{
					result = style.GetThickness();
					isFirstElem = false;
				}
				else if (result != style.GetThickness())
				{
					result = 0;
				}
			};
		m_enumerator(func);
		return result;
	}

	void SetThickess(size_t thichness) override
	{
		FuncWorksWithOutlineStyles func = [&thichness](IOutlineStyle& style)
			{
				style.SetThickess(thichness);
			};
		m_enumerator(func);
	}
private:
	OutlineStyleEnumerator m_enumerator;
};