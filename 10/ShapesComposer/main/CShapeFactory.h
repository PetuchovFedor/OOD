#pragma once
#include "CShape.h"
#include <random>

class CShapeFactory
{
public:
    std::shared_ptr<IShape> CreateShape(const std::string& id, ShapeTypes type, Rect frame)
	{
		return std::make_shared<CShape>(type, frame, id);
	}
};