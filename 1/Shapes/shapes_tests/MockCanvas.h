#pragma once
#include "../main/ICanvas.h"
#include <vector>

class MockCanvas : public gfx::ICanvas
{
public:
	enum class ExecutedMethods
	{
		MoveTo,
		SetColor,
		LineTo,
		DrawEllipse,
		DrawText,
	};

	void MoveTo(double x, double y) override;
	void SetColor(const gfx::Color& color) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double cx, double cy, double rx, double ry) override;
	void DrawText(double left, double top, double fontSize, const std::string& text) override;

	std::vector<ExecutedMethods> GetMethods() const;

	std::vector<std::string> GetArgs() const;

private:
	std::vector<ExecutedMethods> m_executedMethods;
	std::vector<std::string> m_methodArgs;
};