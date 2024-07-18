#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib_pro.h"

class ModernGraphicsLibAdapter : public graphics_lib::ICanvas
{
public:
	ModernGraphicsLibAdapter(modern_graphics_lib_pro::CModernGraphicsRenderer& renderer)
		: m_renderer(renderer)
	{
		m_renderer.BeginDraw();
	}

	void SetColor(uint32_t rgbColor) override
	{
		//Индийский подход
		std::string hexColor = graphics_lib::TransformUint32_tToHex(rgbColor);
		std::string red{ hexColor[0] , hexColor[1] }, 
			green{ hexColor[2] , hexColor[3] },
			blue{ hexColor[4], hexColor[5] };
		float r = std::stoul(red, nullptr, 16) / 255.f;
		float g = std::stoul(green, nullptr, 16) / 255.f;
		float b = std::stoul(blue, nullptr, 16) / 255.f;
		m_color = { r, g, b, 1.f };
	}

	void MoveTo(int x, int y) override
	{
		m_drawingPos = { x, y };

	}

	void LineTo(int x, int y) override
	{
		m_renderer.DrawLine(m_drawingPos, { x, y }, m_color);
		MoveTo(x, y);
	}

	/*modern_graphics_lib_pro::CRGBAColor GetColor() const
	{
		return m_color;
	}*/

	~ModernGraphicsLibAdapter()
	{
		m_renderer.EndDraw();
	}
private:
	modern_graphics_lib_pro::CPoint m_drawingPos = { 0, 0 };
	modern_graphics_lib_pro::CRGBAColor m_color = {0, 0, 0, 0};
	modern_graphics_lib_pro::CModernGraphicsRenderer& m_renderer;
};