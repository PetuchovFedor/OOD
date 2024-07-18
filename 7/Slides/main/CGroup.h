#pragma once
#include "IGroup.h"
#include <vector>
#include "CGroupOutlineStyle.h"
#include "CGroupFillStyle.h"
#include <algorithm>
#include <iterator>
#include <numeric>

class CGroup : public IGroup
{
public:
	CGroup(/*const RectD& rect*/)
		: m_outlineStyle([&shapes = this->m_shapes](FuncWorksWithOutlineStyles func)
			{
				for (auto& shape : shapes)
				{
					//auto& style = ;
					func(shape->GetOutlineStyle());
				}
			})
		, m_fillStyle([&shapes = this->m_shapes](FuncWorksWithStyles func)
			{
				for (auto& shape : shapes)
				{
					//auto& style = shape->GetOutlineStyle();
					func(shape->GetFillStyle());
				}
			})
		//, m_rect(rect)
	{
	}

	RectD GetFrame() const override
	{
		double left = std::numeric_limits<double>::max();
		double right = 0;
		double bottom = 0;
		double top = std::numeric_limits<double>::max();
		bool isEmptyGroup = true;
		std::vector<RectD> rects;
		std::transform(m_shapes.begin(), m_shapes.end(), std::back_inserter(rects),
			[](IShapePtr const& ptr) -> RectD { return ptr->GetFrame(); });
		for (size_t i = 0; i < rects.size(); i++)
		{
			//Нудевые фигуры учитывать а руппы нет
			if (rects[i].height == 0 && rects[i].width == 0)
				continue;
			left = std::min(rects[i].leftTop.x, left);
			right = std::max(rects[i].leftTop.x + rects[i].width, right);
			top = std::min(rects[i].leftTop.y, top);
			bottom = std::max(rects[i].leftTop.y + rects[i].height, bottom);
			isEmptyGroup = false;
		}
		if (isEmptyGroup)
			return { {0, 0}, 0, 0 };
		return RectD({ left, top }, right - left, bottom - top);
	}

	void SetFrame(const RectD& frame) override
	{
		//Исключение будет неожиданным для клиентов класса CShape
		auto rect = GetFrame();
		//Неудачные имена scale
		double scaleHeight = frame.height / rect.height;
		double scaleWidth = frame.width / rect.width;
		for (auto& shape : m_shapes)
		{
			PointD delta(0, 0);
			auto shapeFrame = shape->GetFrame();
			delta.x = (shapeFrame.leftTop.x - rect.leftTop.x) * scaleWidth;
			delta.y = (shapeFrame.leftTop.y - rect.leftTop.y) * scaleHeight;
			shapeFrame.height *= scaleHeight;
			shapeFrame.width *= scaleWidth;
			shapeFrame.leftTop.x = frame.leftTop.x + delta.x;
			shapeFrame.leftTop.y = frame.leftTop.y + delta.y;
			shape->SetFrame(shapeFrame);
		}
	}

	void Draw(ICanvas& canvas) const override
	{
		//лучше range
		for (const auto& shape : m_shapes)
		{
			shape->Draw(canvas);
		}
	}

	size_t GetShapesCount() const override
	{
		return m_shapes.size();
	}

	IShapePtr GetShapeAtIndex(size_t idx) override
	{		
		CheckOutOfShapesRange(idx);
		return m_shapes[idx];
	}

	void InsertShape(IShapePtr shape, size_t idx) override
	{
		if (std::addressof(*shape) == this)
			return;
		if (idx != m_shapes.size())
			CheckOutOfShapesRange(idx);
		m_shapes.insert(m_shapes.begin() + idx, move(shape));	
	}

	void RemoveShape(size_t idx) override
	{
		CheckOutOfShapesRange(idx);
		m_shapes.erase(m_shapes.begin() + idx);
	}

	const IOutlineStyle& GetOutlineStyle() const override
	{
		return m_outlineStyle;
	}

	IOutlineStyle& GetOutlineStyle() override
	{
		return m_outlineStyle;
	}

	const IStyle& GetFillStyle() const override
	{
		return m_fillStyle;
	}

	IStyle& GetFillStyle() override
	{
		return m_fillStyle;
	}

	std::string GetType() const
	{
		return "group";
	}

	const IGroup* GetGroup() const override
	{
		return this;
	}

	IGroup* GetGroup() override
	{
		return this;
	}

private:

	/*RectD DoNewFrameForGroup()
	{
		double left = std::numeric_limits<double>::max();
		double right = 0;
		double bottom = 0;
		double top = std::numeric_limits<double>::max();
		std::vector<RectD> rects;
		std::transform(m_shapes.begin(), m_shapes.end(), std::back_inserter(rects),
			[](IShapePtr const& ptr) -> RectD { return ptr->GetFrame(); });
		for (size_t i = 0; i < rects.size(); i++)
		{
			left = std::min(rects[i].leftTop.x, left);
			right = std::max(rects[i].leftTop.x + rects[i].width, right);
			top = std::min(rects[i].leftTop.y, top);
			bottom = std::max(rects[i].leftTop.y + rects[i].height, bottom);
		}
		m_rect = { {left, top}, right - left, bottom - top };
	}*/

	//void DoNewFrameForGroup()
	//{
	//	double left = std::numeric_limits<double>::max();
	//	double right = 0;
	//	double bottom = 0;
	//	double top = std::numeric_limits<double>::max();
	//	std::vector<RectD> rects;
	//	std::transform(m_shapes.begin(), m_shapes.end(), std::back_inserter(rects),
	//		[](IShapePtr const& ptr) -> RectD { return ptr->GetFrame(); });
	//	for (size_t i = 0; i < rects.size(); i++)
	//	{
	//		left = std::min(rects[i].leftTop.x, left);
	//		right = std::max(rects[i].leftTop.x + rects[i].width, right);
	//		top = std::min(rects[i].leftTop.y, top);
	//		bottom = std::max(rects[i].leftTop.y + rects[i].height, bottom);
	//	}
	//	//m_rect = { {left, top}, right - left, bottom - top };
	//}

	void CheckOutOfShapesRange(size_t idx)
	{
		if (idx >= m_shapes.size())
			throw std::out_of_range("index out of range");
	}
	//Frame не обновится при вложенных группах
	//Пустые группы не должны влиять на frame
	//RectD m_rect = { {0, 0}, 0, 0 };
	std::vector<IShapePtr> m_shapes;
	CGroupOutlineStyle m_outlineStyle;
	CGroupFillStyle m_fillStyle;
};