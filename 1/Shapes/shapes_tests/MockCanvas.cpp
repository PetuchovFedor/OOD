#include "MockCanvas.h"

void MockCanvas::MoveTo(double x, double y)
{
	m_executedMethods.push_back(ExecutedMethods::MoveTo);
	m_methodArgs.push_back(std::to_string(x) + " " + std::to_string(y));
}

void MockCanvas::SetColor(const gfx::Color& color)
{
	m_executedMethods.push_back(ExecutedMethods::SetColor);
	m_methodArgs.push_back(color);
}

void MockCanvas::LineTo(double x, double y)
{
	m_executedMethods.push_back(ExecutedMethods::LineTo);
	m_methodArgs.push_back(std::to_string(x) + " " + std::to_string(y));
}

void MockCanvas::DrawEllipse(double cx, double cy, double rx, double ry)
{
	m_executedMethods.push_back(ExecutedMethods::DrawEllipse);
	m_methodArgs.push_back(std::to_string(cx) + " " + std::to_string(cy)
		+ std::to_string(rx) + " " + std::to_string(ry));
}

void MockCanvas::DrawText(double left, double top, double fontSize, const std::string& text)
{
	m_executedMethods.push_back(ExecutedMethods::DrawText);
	m_methodArgs.push_back(std::to_string(left) + " " + std::to_string(top)
		+ std::to_string(fontSize) + text);
}

std::vector<MockCanvas::ExecutedMethods> MockCanvas::GetMethods() const
{
	return m_executedMethods;
}

std::vector<std::string> MockCanvas::GetArgs() const
{
	return m_methodArgs;
}
