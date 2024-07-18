#include "CEditor.h"
#include <random>

namespace 
{
	void EraseFirstSpaceSymbol(std::string& str)
	{
		//если строка пустая?
		if (str[0] == ' ')
			str.erase(str.begin());
	}

	//Переименовать
	size_t CheckPos(size_t pos)
	{
		return pos == 0 ? pos : pos - 1;
	}

	void CheckImageSizes(int width, int height)
	{
		if (width > 1000 || height > 1000)
			throw std::invalid_argument("Width and height <= 1000px");
	}

}
CEditor::CEditor()
	: m_document(std::make_unique<CDocument>())

{	
	AddMenuItem("InsertParagraph", "insert paragraph into the document. Args: <pos>|end <text>",
		&CEditor::InsertParagraph);
	AddMenuItem("InsertImage", "insert img into th document. Args: <pos>|end <width> <height> <path>", 
		&CEditor::InsertImage);
	AddMenuItem("SetTitle", "change title document. Ars: <newTitle>",
		&CEditor::SetTitle);
	AddMenuItem("List", "show document items", &CEditor::List);
	AddMenuItem("ReplaceText", "replace text paragraph. Args: <pos> <text>",
		&CEditor::ReplaceText);
	AddMenuItem("ResizeImage", "resize image. Args: <pos> <width> <heught>",
		&CEditor::ResizeImage);
	AddMenuItem("DeleteItem", "delete item in document. Args: <pos>",
		&CEditor::DeleteItem);
	m_menu.AddItem("Help", "help", [this](std::istream& args) {
		m_menu.ShowInstructions();
		});
	AddMenuItem("Undo", "do undo", &CEditor::Undo);
	AddMenuItem("Redo", "do redo", &CEditor::Redo);
	AddMenuItem("Save", "save document. Args: <path>",
		&CEditor::Save);
	
}

void CEditor::Start()
{
	m_menu.Run();
}

void CEditor::AddMenuItem(const std::string& shortcut, const std::string& description, MenuHandler handler)
{
	m_menu.AddItem(shortcut, description, std::bind_front(handler, this));
}

void CEditor::InsertParagraph(std::istream& args)
{
	std::string pos;
	args >> pos;
	std::optional<size_t> position = std::nullopt;
	if (pos != "end")
	{		
		position = std::make_optional(CheckPos(std::stoi(pos)));
		//if (position > m_document.)
	}
	std::string text;
	getline(args, text);
	EraseFirstSpaceSymbol(text);
	m_document->InsertParagraph(text, position);
}

void CEditor::InsertImage(std::istream& args)
{
	std::string pos;
	args >> pos;
	std::optional<size_t> position = std::nullopt;
	if (pos != "end")
	{
		position = std::make_optional(CheckPos(std::stoi(pos)));
	}
	int width, height;
	args >> width >> height;
	CheckImageSizes(width, height);
	std::string path;
	getline(args, path);
	EraseFirstSpaceSymbol(path);
	m_document->InsertImage(path, width, height, position);
}

void CEditor::SetTitle(std::istream& args)
{
	std::string title;
	getline(args, title);
	EraseFirstSpaceSymbol(title);
	m_document->SetTitle(title);
}

void CEditor::List(std::istream& args)
{
	std::cout << "Title: " << m_document->GetTitle() << std::endl;
	for (size_t i = 0; i < m_document->GetItemsCount(); i++)
	{
		CConstDocumentItem item = m_document->GetItem(i);
		std::cout << i + 1 << ". ";
		auto img = item.GetImage();
		if (img)
		{
			std::cout << "Image: " << img->GetWidth() << ' '
				<< img->GetHeight() << ' ' << img->GetPath()
				<< std::endl;
		}
		else
		{
			auto paragraph = item.GetParagraph();
			std::cout << "Paragraph: " << paragraph->GetText()
				<< std::endl;
		}
	}
}

void CEditor::ReplaceText(std::istream& args)
{
	size_t position;
	args >> position;
	std::string text;
	getline(args, text);
	EraseFirstSpaceSymbol(text);
	CDocumentItem item = m_document->GetItem(CheckPos(position));
	auto paragraph = item.GetParagraph();
	if (!paragraph)
		throw std::invalid_argument("There is no paragraph in this position");
	paragraph->SetText(text);
}

void CEditor::ResizeImage(std::istream& args)
{
	size_t position;
	args >> position;
	int width, height;
	args >> width >> height;
	CheckImageSizes(width, height);
	CDocumentItem item = m_document->GetItem(CheckPos(position));
	auto img = item.GetImage();
	if (!img)
		throw std::invalid_argument("There is no image in this position");
	img->Resize(width, height);
}

void CEditor::DeleteItem(std::istream& args)
{
	size_t position;
	args >> position;
	m_document->DeleteItem(CheckPos(position));
}

void CEditor::Undo(std::istream& args)
{
	if (m_document->CanUndo())
		m_document->Undo();
	else
		throw std::runtime_error("Operation Undo is unavaible");
}

void CEditor::Redo(std::istream& args)
{
	if (m_document->CanRedo())
		m_document->Redo();
	else
		throw std::runtime_error("Operation Redo is unavaible");
}

void CEditor::Save(std::istream& args)
{
	std::string path;
	getline(args, path);
	EraseFirstSpaceSymbol(path);
	m_document->Save(path);
	m_menu.Exit();
}

