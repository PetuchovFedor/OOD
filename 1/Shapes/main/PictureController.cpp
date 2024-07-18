#include "PictureController.h"
#include "CircleStrategy.h"
#include "LineStrategy.h"
#include "RectangleStrategy.h"
#include "TextStrategy.h"
#include "TriangleStrategy.h"


PictureController::PictureController(shapes::Picture& picture, gfx::ICanvas& canvas, std::istream& input, std::ostream& output)
	: m_picture(picture)
	, m_canvas(canvas)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
			{ "AddShape", [this](std::istream& args) { //std::bind_front(&PictureController::AddShapeComand, this);
				return AddShapeComand(args); } },
			{ "MoveShape", [this](std::istream& args) {
				return MoveShapeComand(args); } },
			{ "MovePicture", [this](std::istream& args) {
				return MovePictureComand(args); } },
			{ "DeleteShape", [this](std::istream& args) {
				return DeleteShapeComand(args); } },
			{ "List", [this](std::istream& args) {
				return WriteListShapesComand(args); } },
			{ "ChangeColor", [this](std::istream& args) {
				return ChangeColorComand(args); } },
			{ "ChangeShape", [this](std::istream& args) {
				return ChangeShapeComand(args); } },
			{ "DrawShape", [this](std::istream& args) {
				return DrawShapeComand(args); } },
			{ "DrawPicture", [this](std::istream& args) {
				return DrawPictureComand(args); } }
		})
{
}

bool PictureController::HandleComand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);
	std::string action;
	strm >> action;
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		return it->second(strm);
	}

	return false;
}

bool PictureController::AddShapeComand(std::istream& args)
{
	//std bind_front, bind_back
	std::string id, color;
	args >> id >> color;
	if (!gfx::IsValidColor(color))
	{
		throw std::invalid_argument("Invalid color");
	}
	try
	{
		std::string type;
		m_picture.AddShape(id, color, CreateStrategy(args));
	}
	catch (std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	return true;
}

bool PictureController::MoveShapeComand(std::istream& args)
{
	std::string id;
	args >> id;
	double dx, dy;
	args >> dx >> dy;
	try
	{
		auto it = m_picture.GetShapeById(id);
		it->Move(Point(dx, dy));
	}
	catch (std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	return true;
}

bool PictureController::MovePictureComand(std::istream& args)
{
	double dx, dy;
	args >> dx >> dy;
	m_picture.Move(Point(dx, dy));
	return true;
}

bool PictureController::DeleteShapeComand(std::istream& args)
{
	std::string id;
	args >> id;
	try
	{
		m_picture.DeleteShape(id);
	}
	catch (std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	return true;
}

bool PictureController::WriteListShapesComand(std::istream& args)
{
	std::vector<std::string> ve = m_picture.ShapesList();
	copy(ve.begin(), ve.end(), std::ostream_iterator<std::string>(m_output, "\n"));
	return true;
}

bool PictureController::ChangeColorComand(std::istream& args)
{
	std::string id, color;
	args >> id >> color;
	try
	{
		if (!gfx::IsValidColor(color))
		{
			throw std::invalid_argument("Invalid color");
		}
		auto it = m_picture.GetShapeById(id);
		it->ChangeColor(color);
	}
	catch (std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	return true;
}

bool PictureController::ChangeShapeComand(std::istream& args)
{
	std::string id, type;
	args >> id;
	//беда с соедининельными линиями на диаграмме
	try
	{
		auto it = m_picture.GetShapeById(id);
		it->ChangeShape(CreateStrategy(args));
	}
	catch (std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	return true;
}

bool PictureController::DrawShapeComand(std::istream& args)
{
	std::string id;
	args >> id;
	try
	{
		auto it = m_picture.GetShapeById(id);
		it->Draw(m_canvas);
	}
	catch (std::exception& e)
	{
		m_output << e.what() << std::endl;
	}
	return true;
}

bool PictureController::DrawPictureComand(std::istream& args)
{
	m_picture.Draw(m_canvas);
	return true;
}

std::unique_ptr<IShapeStrategy> PictureController::CreateStrategy(std::istream& args)
{
	std::string type;
	args >> type;
	if (type == "circle")
	{
		double x, y, r;
		args >> x >> y >> r;
		Point center(x, y);
		return std::make_unique<CircleStrategy>(center, r);
	}
	else if (type == "line")
	{
		double x1, y1, x2, y2;
		args >> x1 >> y1 >> x2 >> y2;
		Point begin(x1, y2);
		Point end(x2, y2);
		return std::make_unique<LineStrategy>(begin, end);
	}
	else if (type == "rectangle")
	{
		double x, y, width, height;
		args >> x >> y >> width >> height;
		Point leftTop(x, y);
		return std::make_unique<RectangleStrategy>(leftTop, width, height);
	}
	else if (type == "text")
	{
		double x, y, fontSize;
		std::string text;
		args >> x >> y >> fontSize;
		if (fontSize < 0)
		{
			throw std::invalid_argument("Font size shoud be > 0");
		}
		Point leftTop(x, y);
		getline(args, text);
		return std::make_unique<TextStrategy>(leftTop, fontSize, text);
	}
	else if (type == "triangle")
	{
		double x1, y1, x2, y2, x3, y3;
		args >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
		Point p1(x1, y1);
		Point p2(x2, y2);
		Point p3(x3, y3);

		return std::make_unique<TriangleStrategy>(p1, p2, p3);
	}
	else
	{
		throw std::runtime_error("unknown shape");
	}
}
