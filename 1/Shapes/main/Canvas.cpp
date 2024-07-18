#include "Canvas.h"
#include <fstream>

const int STROKE_WIDTH = 5;

void Canvas::MoveTo(double x, double y)
{
	m_drawingPos = Point(x, y);
}

void Canvas::SetColor(const gfx::Color& color)
{
	m_colorOfPen = color;
}

void Canvas::LineTo(double x, double y)
{
	std::stringstream line;
	//<line x1 = "10" x2 = "50" y1 = "110" y2 = "150" stroke = "orange" fill = "transparent" stroke - width = "5" / >
	line << "<line x1 = " << R"(")" << m_drawingPos.x << R"(" )"
		<< "y1 = " << R"(")" << m_drawingPos.y << R"(" )" 
		<< "x2 = " << R"(")" << x << R"(" )" << "y2 = " << R"(")" 
		<< y << R"(" )" << "stroke = " << R"(")" << m_colorOfPen << R"(" )"
		<< "stroke-width = " << R"(")" << STROKE_WIDTH << R"(" />)" 
		<< std::endl;
	//c++ 20 попробовать с std format
	MoveTo(x, y);
	m_output << line.str();
}

void Canvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	//<ellipse cx = "75" cy = "75" rx = "20" ry = "5" stroke = "red" fill = "transparent" stroke - width = "5" / >
	std::stringstream line;
	line << "<ellipse cx = " << R"(")" << cx << R"(" )" << "cy = "
		<< R"(")" << cy << R"(" )" << "rx = " << R"(")" << rx
		<< R"(" )" << "ry = " << R"(")" << ry << R"(" )" << "stroke = "
		<< R"(")" << m_colorOfPen << R"(" )" << R"(fill = "transparent" )" << "stroke-width = "
		<< R"(")" << STROKE_WIDTH << R"(" />)"
		<< std::endl;
	m_output << line.str();
}

void Canvas::DrawText(double left, double top, double fontSize, const std::string& text)
{
	/*<text x = "250" y = "180"
		font - family = "Verdana" font - size = "64" fill = "blue" >
		Hello, out there!
		< / text>*/
	std::stringstream line;
	line << "<text x = " << R"(")" << left << R"(" )"
		<< "y = " << R"(")" << top << R"(" )" << "font-size = "
		<< R"(")" << fontSize << R"(" )" << "fill = "
		<< R"(")" << m_colorOfPen << R"(" >)" << text
		<< "</text>" << std::endl;
	m_output << line.str();
}

void Canvas::Save(const std::string& fileName)
{
	std::ofstream output(fileName);
	output << R"(<svg version="1.1" xmlns="http://www.w3.org/2000/svg">)";
	output << m_output.str() << "</svg>" << std::endl;
}
