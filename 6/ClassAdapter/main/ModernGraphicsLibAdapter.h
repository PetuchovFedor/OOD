#pragma once
#include "graphics_lib.h"
#include "modern_graphics_lib.h"

class ModernGraphicsLibAdapter : public graphics_lib::ICanvas, 
	private modern_graphics_lib::CModernGraphicsRenderer
{
public:
	ModernGraphicsLibAdapter(std::ostream& out)
		: CModernGraphicsRenderer(out)
	{
		CModernGraphicsRenderer::BeginDraw();
	}

	void MoveTo(int x, int y) override
	{
		m_drawingPos = { x, y };
	}

	void LineTo(int x, int y) override
	{
		CModernGraphicsRenderer::DrawLine(m_drawingPos, { x, y });
		MoveTo(x, y);
	}

	~ModernGraphicsLibAdapter()
	{
		try
		{
			CModernGraphicsRenderer::EndDraw();
		}
		catch(...)
		{ }
	}
private:
	modern_graphics_lib::CPoint m_drawingPos = { 0, 0 };
};