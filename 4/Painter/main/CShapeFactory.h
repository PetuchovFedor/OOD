#pragma once
#include "IShapeFactory.h"
#include <functional>
#include <map>

class CShapeFactory : public IShapeFactory
{
public:
	CShapeFactory();
	std::unique_ptr<CShape> CreateShape(const std::string& descr) override;
private:
	std::unique_ptr<CShape> CreateRectangle(std::istream& args);
	std::unique_ptr<CShape> CreateTriangle(std::istream& args);
	std::unique_ptr<CShape> CreateEllipse(std::istream& args);
	std::unique_ptr<CShape> CreateRegularPolygon(std::istream& args);
	//std::vector<std::string> SplitStream(std::istream& args);
	Color GetColor(const std::string& color) const;
	using Handler = std::function<std::unique_ptr<CShape>(std::istream& args)>;
	using ActionMap = std::map<std::string, Handler>;
	const std::map<std::string, Color> m_colorMap;
	const ActionMap m_createShapeMap;
};