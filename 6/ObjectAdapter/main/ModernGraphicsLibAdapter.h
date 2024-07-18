#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ModernGraphicsLibAdapter : public  graphics_lib::ICanvas
{
public:
	ModernGraphicsLibAdapter(modern_graphics_lib::CModernGraphicsRenderer& render)
		: m_render(render)
	{
		//BeginDraw и EndDraw не должен вызывать адаптер
		render.BeginDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_drawingPos = { x, y };
	}

	void LineTo(int x, int y) override
	{
		m_render.DrawLine(m_drawingPos, { x, y });
		MoveTo(x, y);
	}

	~ModernGraphicsLibAdapter()
	{
		try
		{
			m_render.EndDraw();
		}
		catch(...)
		{ }
	}
private:
	modern_graphics_lib::CModernGraphicsRenderer& m_render;
	modern_graphics_lib::CPoint m_drawingPos = { 0, 0 };
};
