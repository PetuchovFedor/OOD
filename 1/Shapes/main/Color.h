#pragma once
#include <string>
#include <regex>

namespace gfx
{
	using Color = std::string;
	bool IsValidColor(const Color& str);

}