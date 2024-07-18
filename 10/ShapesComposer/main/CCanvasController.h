#pragma once
#include "ICanvasController.h"
#include "CPicture.h"

class CCanvasController : public ICanvasController
{
public:
	CCanvasController(CPicture* picture)
		:m_picture(picture)
	{}

private:

	void DeleteItem(const std::string& id) override
	{
		m_picture->DeleteItem(id);
	}

	void SetSize(Size size) override
	{
		m_picture->SetSize(size);
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