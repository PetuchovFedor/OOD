#pragma once
#include "CShape.h"
#include <vector>
#include <memory>

class CPictureDraft
{
public:
	size_t GetShapeCount() const
	{
		return m_draft.size();
	}

	CShape* GetShape(size_t index)
	{
		return m_draft[index].get();
	}

	void AddShape(std::unique_ptr<CShape> shape)
	{
		m_draft.push_back(move(shape));
	}
private:
	std::vector<std::unique_ptr<CShape>> m_draft;
};
