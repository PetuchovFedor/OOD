#include "Picture.h"
#include <stdexcept>
#include <sstream>

void shapes::Picture::Move(Point vector)
{
	for (size_t i = 0; i < m_shapesList.size(); i++)
	{
		m_shapes.at(m_shapesList[i])->Move(vector);
	}
}

void shapes::Picture::AddShape(const std::string& id, gfx::Color color, std::unique_ptr<IShapeStrategy> strategy)
{
	auto it = m_shapes.find(id);

	if (it != m_shapes.end())
	{
		throw std::runtime_error("There is already a shape with this id");
	}
	m_shapes.insert({ id, std::make_shared<Shape>(Shape(id, color, std::move(strategy))) });
	m_shapesList.push_back(id);
}

void shapes::Picture::DeleteShape(const std::string& id)
{
	auto it = m_shapes.find(id);

	if (it == m_shapes.end())
	{
		throw std::runtime_error("There is not shape with this id");
	}
	m_shapes.erase(it);
	m_shapesList.erase(std::find(m_shapesList.begin(), m_shapesList.end(), id));
}

void shapes::Picture::Draw(gfx::ICanvas& canvas)
{
	for (size_t i = 0; i < m_shapesList.size(); i++)
	{
		m_shapes.at(m_shapesList[i])->Draw(canvas);
	}
}

std::shared_ptr<shapes::Shape> shapes::Picture::GetShapeById(const std::string& id)
{
	auto it = m_shapes.find(id);
	if (it == m_shapes.end())
	{
		throw std::runtime_error("There is not shape with this id");
	}
	return it->second;
}

std::vector<std::string> shapes::Picture::ShapesList() const
{
	std::vector<std::string> ve;
	for (size_t i = 0; i < m_shapesList.size(); i++)
	{
		std::stringstream ss;
		ss << i + 1 << ' ' << m_shapes.at(m_shapesList[i])->ToString();
		ve.push_back(ss.str());
	}
	return ve;
}