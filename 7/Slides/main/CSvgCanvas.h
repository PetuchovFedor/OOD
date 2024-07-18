#pragma once
#include "ICanvas.h"
#include <sstream>
#include <fstream>

class CSvgCanvas : public ICanvas
{
public:

	/*CSvgCanvas()
	
	{}*/

	void SetLineColor(RGBAColor color) override
	{
		m_outlineColor = color;
	}

	void FillPolygon(const std::vector<PointD>& points, RGBAColor color) override
	{
		m_output << "<path d=\"M" << points[0].x << ' '
			<< points[0].y << ' ';
		bool isFirstIter = true;
		for (const auto& [x, y] : points)
		{
			if (isFirstIter)
			{
				isFirstIter = false;
				continue;
			}
			m_output << "L " << x << ' ' << y << ' ';
		}
		m_output << "Z\" fill=\"" << TransformRGBAToHex(color) << "\" />" << std::endl;
		//m_fillColor = color;
	}	

	void MoveTo(PointD to) override
	{
		m_drawingPenCoord = to;
	}

	void LineTo(PointD to) override
	{
		//<line x1 = "10" x2 = "50" y1 = "110" y2 = "150" stroke = "orange" fill = "transparent" stroke - width = "5" / >
		std::stringstream line;
		line << "<line x1=\"" << m_drawingPenCoord.x
			<< "\" y1=\"" << m_drawingPenCoord.y
			<< "\" x2=\"" << to.x << "\" y2=\""
			<< to.y << "\" stroke=\"" << TransformRGBAToHex(m_outlineColor)
			<< "\" stroke-width =\"" << m_thickness
			<< "\" />" << std::endl;
		MoveTo(to);
		m_output << line.str();
	}

	void SetThickessLine(size_t thickness) override
	{
		m_thickness = thickness;
	}

	void DrawEllipse(PointD leftTop, double width, double height) override
	{
		std::stringstream line;
		line << "<ellipse cx = \"" << leftTop.x + width / 2 << "\" cy=\""
			<< leftTop.y + height / 2 << "\" rx =\"" << width / 2
			<< "\" ry =\"" << height / 2 << "\" stroke=\""
			<< TransformRGBAToHex(m_outlineColor) << "\" " << "fill = \"transparent\" " 
			<< "stroke-width =\"" << m_thickness << "\" />"
			<< std::endl;
		m_output << line.str();
	}

	void FillEllipse(PointD leftTop, double width, double height, RGBAColor color) override
	{
		std::stringstream line;
		line << "<ellipse cx = \"" << leftTop.x + width / 2 << "\" cy=\""
			<< leftTop.y + height / 2 << "\" rx =\"" << width / 2
			<< "\" ry =\"" << height / 2
			<< "\" " << "fill = \"" << 
			TransformRGBAToHex (color) << "\" />"
			<< std::endl;
		m_output << line.str();
	}

	void Save(const std::string& fileName)
	{
		std::ofstream output(fileName);
		output << R"(<svg version="1.1"  width = "1000" height = "1000" xmlns="http://www.w3.org/2000/svg">)" 
			<< std::endl;
		output << m_output.str() << "</svg>" << std::endl;
	}

private:
	PointD m_drawingPenCoord = { 0, 0 };
	RGBAColor m_outlineColor = 0xffffff;
	std::stringstream m_output;
	size_t m_thickness;
};