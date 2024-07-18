#pragma once
#include "CommonTypes.h"
#include "IPictureItem.h"

enum class ShapeTypes
{
	RECTANGLE,
	ELLIPSE,
	TRIANGLE
};

class IShape: public IPictureItem
{
public:
	virtual ShapeTypes GetType() const = 0;
	virtual ~IShape() = default;
};

using IShapePtr = std::shared_ptr<IShape>;