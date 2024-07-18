#pragma once
#include "CPictureDraft.h"
#include "ICanvas.h"

class CPainter
{
public:
	void DrawPicture(CPictureDraft& draft, ICanvas& canvas)
	{
		for (size_t i = 0; i < draft.GetShapeCount(); i++)
		{
			auto shape = draft.GetShape(i);
			shape->Draw(canvas);
		}
	}
};