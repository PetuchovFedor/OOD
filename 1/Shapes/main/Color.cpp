#include "Color.h"

bool gfx::IsValidColor(const Color& str)
{
	std::regex hexRegex("^#([0-9A-Fa-f]+)$");
	return std::regex_match(str, hexRegex);
}
