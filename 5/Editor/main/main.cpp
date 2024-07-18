#include "CEditor.h"
#include <iostream>
#include <filesystem>
#include "ChangeStringCommand.h"
#include <windows.h>
using namespace std;

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "Russian");
	CEditor editor;
	editor.Start();
	//std::string  s = fs::current_path().string();
	//fs::create_directory("Editor/images");
	//// = ;
	//fs::path pa = "D:/User Files/123.txt";
	//fs::copy_file(pa, "o.txt");
	//CDocument doc;
	//doc.InsertImage("123", 300, 300, std::nullopt);
	//CDocumentItem item = doc.GetItem(0);
	//std::cout << item.GetImage()->GetWidth() << ' ' << item.GetImage()->GetHeight() << std::endl;
	//item.GetImage()->Resize(250, 350);
	////std::shared_ptr<CParagraphImpl> p = item.GetParagraph()/*->SetText("123");*/;
	//std::cout << item.GetImage()->GetWidth() << ' ' << item.GetImage()->GetHeight() << std::endl;
	//doc.Undo();
	//std::cout << item.GetImage()->GetWidth() << ' ' << item.GetImage()->GetHeight() << std::endl;
	//doc.Redo();
	//std::cout << item.GetImage()->GetWidth() << ' ' << item.GetImage()->GetHeight() << std::endl;

}
