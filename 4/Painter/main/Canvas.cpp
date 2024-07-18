#include "Canvas.h"
#include <fstream>

const int STROKE_WIDTH = 5;

void Canvas::SetColor(Color color)
{
	m_colorOfPen = color;
}

void Canvas::DrawLine(Point from, Point to)
{
	std::stringstream line;
	line << "<line x1 = " << "\"" << from.x << R"(" )"
		<< "y1 = " << "\"" << from.y << "\" "
		<< "x2 = " << "\"" << to.x << "\" " << "y2 = " << "\""
		<< to.y << "\" " << "stroke = " << "\"" << ToHex(m_colorOfPen) << "\" "
		<< "stroke-width = " << "\"" << STROKE_WIDTH << "\" />"
		<< std::endl;
	m_output << line.str();
}

void Canvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	std::stringstream line;
	line << "<ellipse cx = " << "\"" << cx << "\" " << "cy = "
		<< "\"" << cy << "\" " << "rx = " << "\"" << rx
		<< "\" " << "ry = " << "\"" << ry << "\" " << "stroke = "
		<< "\"" << ToHex(m_colorOfPen) << "\" " << R"(fill = "transparent" )" << "stroke-width = "
		<< "\"" << STROKE_WIDTH << "\" />"
		<< std::endl;
	m_output << line.str();
}

void Canvas::Save(const std::string& fileName)
{
	std::ofstream output(fileName);
	output << R"(<svg version="1.1" xmlns="http://www.w3.org/2000/svg">)";
	output << m_output.str() << "</svg>" << std::endl;
}

std::string Canvas::ToHex(Color color)
{
	std::string result;
	switch (color)
	{
	case Color::Green:
		result = "#00ff00";
		break;
	case Color::Red:
		result = "#ff0000";
		break;
	case Color::Blue:
		result = "#0000ff";
		break;
	case Color::Yellow:
		result = "#ffff00";
		break;
	case Color::Pink:
		result = "#ffc0cb";
		break;
	case Color::Black:
		result = "#000000";
		break;
	default:
		break;
	}
	return result;
}


