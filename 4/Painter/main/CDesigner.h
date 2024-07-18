#pragma once
#include "IDesigner.h"
#include "CPictureDraft.h"
#include "IShapeFactory.h"
#include <iostream>

class CDesigner : public IDesigner
{
public:
	CDesigner(const std::shared_ptr<IShapeFactory>& factory)
		: m_factory(factory)
	{}

	CPictureDraft CreateDraft(std::istream& strm) const override
	{
		CPictureDraft draft;
		std::string line;
		
		while (getline(strm, line))
		{
			try
			{
				auto shape = m_factory->CreateShape(line);
				draft.AddShape(move(shape));
			}
			catch (const std::exception& e)
			{
				std::cout << e.what() << std::endl;
			}			
		}
		return draft;
	}
private:
	std::shared_ptr<IShapeFactory> m_factory;
};