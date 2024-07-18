#pragma once
#include "Point.h"
#include "ICanvas.h"

class IShapeStrategy
{
public:
	virtual ~IShapeStrategy() = default;
	virtual void Move(Point vector) = 0;
	virtual void Draw(gfx::ICanvas& canvas) = 0;
	virtual std::string GetValueParamsInString() const = 0;
	virtual std::string GetType() const = 0;
};