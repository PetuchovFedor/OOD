#pragma once
#include "CommonTypes.h"
#include <optional>
#include <functional>

class IStyle
{
public:
	virtual std::optional<RGBAColor> GetColor() const = 0;
	virtual void SetColor(const RGBAColor& rgbaColor) = 0;
	virtual ~IStyle() = default;
};

using FuncWorksWithStyles = std::function<void(IStyle&)>;
using StyleEnumerator = std::function<void(FuncWorksWithStyles)>;
