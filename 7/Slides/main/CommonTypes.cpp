#include "CommonTypes.h"
#include <format>
#include <sstream>

std::string TransformRGBAToHex(RGBAColor color)
{
	std::stringstream stream;
	//stream << 
	stream << std::format("{:#010x}", color);
	auto result = stream.str();
	result.erase(result.begin());
	result.erase(result.begin());
	result.insert(result.begin(), '#');
	//stream /*<< std::setfill('0') << std::setw(sizeof(uint32_t) * 2)*/<< std::hex << color;
	return result;
}