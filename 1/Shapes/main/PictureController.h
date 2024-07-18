#pragma once
#include "Picture.h"
#include <vector>
#include <map>
#include <functional>
#include <memory>

class PictureController
{
public:
	PictureController(shapes::Picture& picture, gfx::ICanvas& canvas, std::istream& input, std::ostream& output);
	bool HandleComand();

private:
	bool AddShapeComand(std::istream& args);
	bool MoveShapeComand(std::istream& args);
	bool MovePictureComand(std::istream& args);
	bool DeleteShapeComand(std::istream& args);
	bool WriteListShapesComand(std::istream& args);
	bool ChangeColorComand(std::istream& args);
	bool ChangeShapeComand(std::istream& args);
	bool DrawShapeComand(std::istream& args);
	bool DrawPictureComand(std::istream& args);
	std::unique_ptr<IShapeStrategy> CreateStrategy(std::istream& args);

private:
	using Handler = std::function<bool(std::istream& args)>;

	using ActionMap = std::map<std::string, Handler>;

	std::istream& m_input;
	std::ostream& m_output;

	shapes::Picture& m_picture;
	gfx::ICanvas& m_canvas;
	const ActionMap m_actionMap;
};
