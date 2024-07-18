#pragma once
#include "CSlide.h"
#include <iostream>

class CSlideController
{
public:
	CSlideController(std::istream& input, std::ostream& output, ICanvas& canvas);
	bool HandleCommand();
private:

	bool AddShapeCommand(std::istream& args);

	bool RemoveShapeCommand(std::istream& args);

	bool ChangeLineColorCommand(std::istream& args);

	bool ChangeFillColorCommand(std::istream& args);

	bool ChangeLineThicknessCommand(std::istream& args);

	bool ChangeFrameCommand(std::istream& args);

	bool GroupShapesCommand(std::istream& args);

	bool ListCommand(std::istream& args);
	
	bool DrawShapeCommand(std::istream& args);

	bool DrawSlideCommand(std::istream& args);

	bool Help(std::istream& args);

	RectD ReadFrame(std::istream& args);
	using Handler = std::function<bool(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;

	CSlide m_slide;
	std::istream& m_input;
	std::ostream& m_output;
	ICanvas& m_canvas;
	const ActionMap m_actionMap;
};