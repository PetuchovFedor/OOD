#pragma once
#include "CPictureDraft.h"
#include <sstream>

//лишнее
class IDesigner
{
public:
	virtual CPictureDraft CreateDraft(std::istream& strm) const = 0;
	virtual ~IDesigner() = default;
};