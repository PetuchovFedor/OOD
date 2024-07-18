#pragma once
#include "IStyle.h"

class IOutlineStyle : public IStyle
{
public:
	virtual size_t GetThickness() const = 0;
	virtual void SetThickess(size_t thichness) = 0;
	virtual ~IOutlineStyle() = default;
};

using FuncWorksWithOutlineStyles = std::function<void(IOutlineStyle&)>;
using OutlineStyleEnumerator = std::function<void(FuncWorksWithOutlineStyles)>;
