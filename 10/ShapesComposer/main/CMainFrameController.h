#pragma once
#include "IMainFrameController.h"
#include "CPicture.h"

class CMainFrameController :
	public IMainFrameController
{
public:
	CMainFrameController(CPicture* picture)
		:m_picture(picture)
	{}
private:
	void AddShape(IShapePtr item) override
	{
		m_picture->AddShape(move(item));
	}

	void AddImage(IImagePtr item) override
	{
		m_picture->AddImage(move(item));
	}

	void DeleteItem(const std::string& id) override
	{
		m_picture->DeleteItem(id);
	}

	void Undo() override
	{
		m_picture->Undo();
	}

	void Redo() override
	{
		m_picture->Redo();
	}

	CPicture* m_picture;
};