#pragma once
#include <map>
#include "Shape.h"
#include <vector>
namespace shapes
{
	class Picture
	{
	public:
		void Move(Point vector);

		void AddShape(const std::string& id, gfx::Color color,
			std::unique_ptr<IShapeStrategy> strategy);

		void DeleteShape(const std::string& id);

		void Draw(gfx::ICanvas& canvas);

		std::shared_ptr<Shape> GetShapeById(const std::string& id);

		std::vector<std::string> ShapesList() const;

	private:
		std::map<std::string, std::shared_ptr<Shape>> m_shapes;
		std::vector<std::string> m_shapesList;
	};
}