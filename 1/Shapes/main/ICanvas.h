#pragma once
#include "Color.h"

namespace gfx
{
	class ICanvas
	{
	public:
		virtual void MoveTo(double x, double y) = 0;
		virtual void SetColor(const Color& color) = 0;
		virtual void LineTo(double x, double y) = 0;
		virtual void DrawEllipse(double cx, double cy, double rx, double ry) = 0;
		virtual void DrawText(double left, double top, double fontSize, const std::string& text) = 0;
		//Выяснить для чего нужен виртуальный деструктор
		virtual ~ICanvas() = default;
	};
}