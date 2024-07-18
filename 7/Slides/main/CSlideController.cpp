#include "CSlideController.h"
#include <sstream>
#include <string>
#include "CRectangle.h"
#include "CTriangle.h"
#include "CEllipse.h"
#include <format>

CSlideController::CSlideController(std::istream& input, std::ostream& output, ICanvas& canvas)
	: m_canvas(canvas)
	, m_input(input)
	, m_output(output)
	, m_actionMap({
		{"AddShape", std::bind_front(&CSlideController::AddShapeCommand, this)},
		{"RemoveShape", std::bind_front(&CSlideController::RemoveShapeCommand, this)},
		{"ChangeLineColor", std::bind_front(&CSlideController::ChangeLineColorCommand, this)},
		{"ChangeFillColor", std::bind_front(&CSlideController::ChangeFillColorCommand, this)},
		{"ChangeLineThickness", std::bind_front(&CSlideController::ChangeLineThicknessCommand, this)},
		{"ChangeFrame", std::bind_front(&CSlideController::ChangeFrameCommand, this)},
		{"GroupShapes", std::bind_front(&CSlideController::GroupShapesCommand, this)},
		{"List", std::bind_front(&CSlideController::ListCommand, this)},
		{"DrawShape", std::bind_front(&CSlideController::DrawShapeCommand, this)},
		{"DrawSlide", std::bind_front(&CSlideController::DrawSlideCommand, this)},
		{"Help", std::bind_front(&CSlideController::Help, this)},
		})
{
}

bool CSlideController::HandleCommand()
{
	std::string commandLine;
	getline(m_input, commandLine);
	std::istringstream strm(commandLine);
	std::string action;
	strm >> action;
	auto it = m_actionMap.find(action);
	if (it != m_actionMap.end())
	{
		try
		{
			return it->second(strm);
		}
		catch (const std::exception& e)
		{
			m_output << e.what() << std::endl;
		}
	}

	return false;
}

bool CSlideController::AddShapeCommand(std::istream& args)
{
	std::string  type;
	args >> type;
	
	RectD frame = ReadFrame(args);
	IShapePtr shape;
	if (type == "rect")
	{
		shape = std::make_shared<CRectangle>(frame);
	}
	else if (type == "triangle")
	{
		shape = std::make_shared<CTriangle>(frame);
	}
	else if (type == "ellipse")
	{
		shape = std::make_shared<CEllipse>(frame);
	}
	else
	{
		throw std::invalid_argument("There are no such figures");
	}
	std::string color1, color2;
	args >> color1;
	color1.erase(color1.begin());
	shape->GetOutlineStyle().SetColor(std::stoull(color1, nullptr, 16));
	if (!args.eof())
	{
		size_t thickness;
		args >> thickness;
		shape->GetOutlineStyle().SetThickess(thickness);
		if (!args.eof())
		{
			args >> color2;
			color2.erase(color2.begin());
			shape->GetFillStyle().SetColor(std::stoull(color2, nullptr, 16));
		}
	}
	m_slide.AddShape(move(shape));
	return true;
}

bool CSlideController::RemoveShapeCommand(std::istream& args)
{
	std::size_t idx;
	args >> idx;
	m_slide.RemoveShape(idx - 1);
	return true;
}

bool CSlideController::ChangeLineColorCommand(std::istream& args)
{
	size_t idx;
	std::string color;
	args >> idx >> color;
	color.erase(color.begin());
	m_slide.GetShape(idx - 1)->GetOutlineStyle().SetColor(std::stoull(color, nullptr, 16));
	return true;
}

bool CSlideController::ChangeFillColorCommand(std::istream& args)
{
	size_t idx;
	std::string color;
	args >> idx >> color;
	color.erase(color.begin());
	m_slide.GetShape(idx - 1)->GetFillStyle().SetColor(std::stoull(color, nullptr, 16));
	return true;
}

bool CSlideController::ChangeLineThicknessCommand(std::istream& args)
{
	size_t idx, thickness;
	args >> idx >> thickness;
	m_slide.GetShape(idx - 1)->GetOutlineStyle().SetThickess(thickness);
	return true;
}

bool CSlideController::ChangeFrameCommand(std::istream& args)
{
	std::size_t idx;
	args >> idx;
	RectD frame = ReadFrame(args);
	m_slide.GetShape(idx - 1)->SetFrame(frame);
	return true;
}

bool CSlideController::GroupShapesCommand(std::istream& args)
{
	std::vector<std::pair<std::size_t, size_t>> idsAndPoses;
	size_t idx, pos;
	while (args >> idx && args >> pos)
	{
		idsAndPoses.push_back({ idx - 1, pos - 1 });
	}
	m_slide.GroupShapes( idsAndPoses);
	return true;
}

bool CSlideController::ListCommand(std::istream& args)
{
	for (size_t i = 0; i < m_slide.GetCountShapes(); i++)
	{
		auto shape = m_slide.GetShape(i);
		m_output << i + 1 << ' ' << shape->GetType() << ' ';
		auto frame = shape->GetFrame();
		m_output << frame.leftTop.x << ' ' << frame.leftTop.y
			<< ' ' << frame.width << ' ' << frame.height << ' ';
		const auto& lineStyle = shape->GetOutlineStyle();
		const auto& fillStyle = shape->GetFillStyle();
		if (lineStyle.GetColor())
			m_output << TransformRGBAToHex(lineStyle.GetColor().value()) << ' ';
		if (lineStyle.GetThickness() != 0)
			m_output << lineStyle.GetThickness() << ' ';
		if (fillStyle.GetColor())
			m_output << TransformRGBAToHex(fillStyle.GetColor().value());
		m_output << std::endl;
		//m_output << lineStyle.GetColor())
	}
	return true;
}

bool CSlideController::DrawShapeCommand(std::istream& args)
{
	size_t idx;
	args >> idx;
	m_slide.GetShape(idx - 1)->Draw(m_canvas);
	return true;
}

bool CSlideController::DrawSlideCommand(std::istream& args)
{
	m_slide.Draw(m_canvas);
	return true;
}

bool CSlideController::Help(std::istream& args)
{
	m_output << "Avaible command: " << std::endl;
	m_output << "AddShape <type> <frame>(leftTope & width &height) ";
	m_output << "line color ?line thickness ?fill color" << std::endl;
	m_output << "RemoveShape <idx>" << std::endl;
	m_output << "ChangeLineColor <idx> <color>" << std::endl;
	m_output << "ChangeLineThickness <idx> <thickness>" << std::endl;
	m_output << "ChangeFillColor <idx> <color>" << std::endl;
	m_output << "ChangeFrame <idx> <frame>" << std::endl;
	m_output << "GroupShapes <idx1> <pos1> <idx2> <pos2> ... <idxn> <posn>" 
		<< std::endl;
	m_output << "List" << std::endl;
	m_output << "DrawShape <idx>" << std::endl;
	m_output << "DrawSlide" << std::endl;
	return false;
}

RectD CSlideController::ReadFrame(std::istream& args)
{
	double left, top, width, height;
	args >> left >> top >> width >> height;
	return RectD({left, top}, width, height);
}
