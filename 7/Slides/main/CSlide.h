#pragma once
#include "IGroup.h"
#include <map>
#include "CGroup.h"

class CSlide : public IDrawable
{
public:	
	void AddShape(IShapePtr&& shape)
	{
		auto it = std::find(m_shapes.begin(), m_shapes.end(), shape);
		if (it != m_shapes.end())
		{
			throw std::runtime_error("Shape with this is already on slide");
		}
		m_shapes.push_back(move(shape));
	}

	void RemoveShape(size_t idx)
	{
		CheckAvailabilityOfShape(idx);
		m_shapes.erase(m_shapes.begin() + idx);
	}

	IShapePtr GetShape(size_t idx)
	{
		CheckAvailabilityOfShape(idx);
		return m_shapes[idx];
	}
	
	const IShapePtr GetShape(size_t idx) const
	{
		return m_shapes[idx];
	}

	void GroupShapes( 
		const std::vector<std::pair<size_t, size_t>>& shapesIdxWithPosesInsertions)
	{
		std::shared_ptr<IGroup> g = std::make_shared<CGroup>();
		//auto shapesCopy(m_shapes);
		for (const auto& [idx, posInsertion] : shapesIdxWithPosesInsertions)
		{
			CheckAvailabilityOfShape(idx);
			g->InsertShape(m_shapes[idx], posInsertion);
			//m_shapes.erase(shapesCopy[idx]);
		}
		auto shapesCopy(m_shapes);
		for (size_t i = 0; i < shapesIdxWithPosesInsertions.size(); i++)
		{
			for (auto it = m_shapes.begin(); it < m_shapes.end(); it++)
			{
				if (*it == shapesCopy[shapesIdxWithPosesInsertions[i].first])
				{
					m_shapes.erase(it);
					break;
				}
			}			
		}
		m_shapes.push_back(move(g));
	}

	void Draw(ICanvas& canvas) const override
	{
		for (auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

	size_t GetCountShapes() const
	{
		return m_shapes.size();
	}

private:

	void CheckAvailabilityOfShape(size_t idx)
	{		
		if (idx >= m_shapes.size())
		{
			throw std::runtime_error("Shape with this is index not exist on slide");
		}
	}
	std::vector<IShapePtr> m_shapes;
};