#include "CShapeFactory.h"
#include <sstream>
#include"CRectangle.h"
#include "CTriangle.h"
#include "CEllipse.h"
#include "CRegularPolygon.h"

namespace
{
	std::vector<std::string> SplitStream(std::istream& args)
	{
		std::vector<std::string> result;
		std::string str;
		while (args >> str)
		{
			result.push_back(str);
		}
		return result;
	}
}
CShapeFactory::CShapeFactory()
	: m_createShapeMap({
		{"rectangle", std::bind_front(&CShapeFactory::CreateRectangle, this)},
		{"triangle", std::bind_front(&CShapeFactory::CreateTriangle, this)},
		{"ellipse", std::bind_front(&CShapeFactory::CreateEllipse, this)},
		{"polygon", std::bind_front(&CShapeFactory::CreateRegularPolygon, this)}
		})
	, m_colorMap({
		{"green", Color::Green },
		{"red", Color::Red },
		{"blue", Color::Blue },
		{"yellow", Color::Yellow },
		{"pink", Color::Pink },
		{"black", Color::Black },
		})
{
}

std::unique_ptr<CShape> CShapeFactory::CreateShape(const std::string& descr)
{
	std::stringstream strm(descr);
	std::string type;
	strm >> type;
	auto it = m_createShapeMap.find(type);
	if (it != m_createShapeMap.end())
	{
		return it->second(strm);
	}
	else
	{
		throw std::invalid_argument("There is no such type of shape");
	}
}

std::unique_ptr<CShape> CShapeFactory::CreateRectangle(std::istream& args)
{
	std::vector<std::string> params = SplitStream(args);
	if (params.size() != 5)
	{
		throw std::runtime_error("params for rectangle shoud be 5");
	}
	Color color = GetColor(params[0]);
	Point leftTop;
	leftTop.x = std::stod(params[1]);
	leftTop.y = std::stod(params[2]);
	Point rightBot;
	rightBot.x = std::stod(params[3]);
	rightBot.y = std::stod(params[4]);
	return std::make_unique<CRectangle>(color, leftTop, rightBot);
}

std::unique_ptr<CShape> CShapeFactory::CreateTriangle(std::istream& args)
{

	std::vector<std::string> params = SplitStream(args);
	if (params.size() != 7)
	{
		throw std::runtime_error("params for triangle shoud be 7");
	}
	Color color = GetColor(params[0]);
	Point vertex1;
	vertex1.x = std::stod(params[1]);
	vertex1.y = std::stod(params[2]);
	Point vertex2;
	vertex2.x = std::stod(params[3]);
	vertex2.y = std::stod(params[4]);
	Point vertex3;
	vertex3.x = std::stod(params[5]);
	vertex3.y = std::stod(params[6]);
	return std::make_unique<CTriangle>(color, vertex1, vertex2, vertex3);
}

std::unique_ptr<CShape> CShapeFactory::CreateEllipse(std::istream& args)
{
	std::vector<std::string> params = SplitStream(args);
	if (params.size() != 5)
	{
		throw std::runtime_error("params for ellipse shoud be 5");
	}
	Color color = GetColor(params[0]);
	Point center;
	center.x = std::stod(params[1]);
	center.y = std::stod(params[2]);
	double horRadius = std::stod(params[3]);
	double verRadius = std::stod(params[4]);

	return std::make_unique<CEllipse>(color, center, horRadius, verRadius);
}

std::unique_ptr<CShape> CShapeFactory::CreateRegularPolygon(std::istream& args)
{
	std::vector<std::string> params = SplitStream(args);
	if (params.size() != 5)
	{
		throw std::runtime_error("params for regular polygon shoud be 5");
	}
	Color color = GetColor(params[0]);
	unsigned countPoint = std::stoi(params[1]);
	Point center;
	center.x = std::stod(params[2]);
	center.y = std::stod(params[3]);
	double radius = std::stod(params[4]);

	return std::make_unique<CRegularPolygon>(color, countPoint, center, radius);
}

Color CShapeFactory::GetColor(const std::string& color) const
{
	if (m_colorMap.find(color) == m_colorMap.end())
	{
		throw std::invalid_argument("Incorrect color entered");
	}
	return m_colorMap.at(color);
}
