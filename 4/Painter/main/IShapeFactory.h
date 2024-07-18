#pragma once
#include "CShape.h"
#include <string>
#include <memory>

class IShapeFactory
{
public:
	virtual std::unique_ptr<CShape> CreateShape(const std::string& descr) = 0;
	virtual ~IShapeFactory() = default;
};