#pragma once
#include <cstdint>
#include "IShapeStrategy.h"
#include <memory>

namespace shapes
{
	class Shape
	{
	public:
		Shape(const std::string& id, gfx::Color color,
			std::unique_ptr<IShapeStrategy> strategy)
			: m_id(id)
			, m_color(color)
			, m_strategy(std::move(strategy))
		{}

		void ChangeShape(std::unique_ptr<IShapeStrategy> strategy)
		{
			m_strategy.reset();
			m_strategy = std::move(strategy);
		}

		void Move(Point vector)
		{
			m_strategy->Move(vector);
		}

		std::string GetId() const
		{
			return m_id;
		}

		gfx::Color GetColor() const
		{
			return m_color;
		}

		std::string ToString() const
		{
			std::string result;
			result = m_strategy->GetType() + ' ' + m_id + ' ' + m_color + ' '
				+ m_strategy->GetValueParamsInString();
			return result;
		}

		void ChangeColor(const gfx::Color& newColor)
		{
			m_color = newColor;
		}

		void Draw(gfx::ICanvas& canvas)
		{
			canvas.SetColor(m_color);
			m_strategy->Draw(canvas);
		}
	private:
		gfx::Color m_color;
		std::string m_id;
		std::unique_ptr<IShapeStrategy> m_strategy;
	};


}