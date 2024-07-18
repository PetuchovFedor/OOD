#include "CDocument.h"
#include "CParagraph.h"
#include "CParagraphAndHistory.h"
#include "CImageAndHistory.h"
#include "CImage.h"
#include "InsertItemCommand.h"
#include "DeleteItemCommand.h"
#include "ChangeStringCommand.h"
#include <map>
#include <fstream>

namespace
{
    std::string CreateRandomString()
    {
        std::random_device dev;
        std::mt19937 rng(dev());
        std::uniform_int_distribution<int> dist('a', 'z');
        std::string rndStr(6, ' ');
        for (auto& ch : rndStr)
        {
            ch = dist(rng);
        }
        return rndStr;
    }

    std::filesystem::path GenerateNewNameForImg(const std::string& path)
    {
        std::filesystem::path pathOrigin(path);
        std::string fileName = CreateRandomString();
        fileName += pathOrigin.extension().string();
        return std::filesystem::path(fileName);
    }

    const std::map<char, std::string> ENCODE_SYMBOLS
    {
        {'&', "&amp;"},
        {'<', "&lt;"},
        {'>', "&gt;"},
        {'\"', "&quot;"},
        {'\'', "&#39;"}
    };

    std::string EncodeText(const std::string& text)
    {
        
        std::string encodeString;
        for (auto& ch : text)
        {
            if (ENCODE_SYMBOLS.find(ch) != ENCODE_SYMBOLS.end())
            {
                encodeString += ENCODE_SYMBOLS.at(ch);
            }
            else
            {
                encodeString.push_back(ch);
            }
        }
        return encodeString;
    }
}

CDocument::CDocument()
{
    auto tmpDir = std::filesystem::current_path();
    m_pathToTmpImagesDir = tmpDir / "images";
    if (std::filesystem::exists(m_pathToTmpImagesDir))
    {
        m_pathToTmpImagesDir = tmpDir / CreateRandomString();
    }
    std::filesystem::create_directory(m_pathToTmpImagesDir);
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string& text, std::optional<size_t> position)
{
    if (position.has_value())
        CheckPosForException(position.value());
    std::shared_ptr<IParagraph> p = std::make_shared<CParagraph>(text);
    std::shared_ptr<IParagraph> pAndHistory = std::make_shared<CParagraphAndHistory>(p, m_history);
    CDocumentItem item(pAndHistory);
    ICommandPtr command = std::make_unique<InsertItemCommand>(m_items, item, position);
    m_history.AddAndExecuteCommand(move(command));
    return p;
}

std::shared_ptr<IImage> CDocument::InsertImage(const std::string& path, int width, int height, std::optional<size_t> position)
{
    if (position.has_value())
        CheckPosForException(position.value());
    auto newName = GenerateNewNameForImg(path);
    std::string newPath = m_pathToTmpImagesDir.stem().string() + "/" + newName.string();
    std::filesystem::copy_file(path, newPath, std::filesystem::copy_options::overwrite_existing);
    std::shared_ptr<IImage> img = std::make_shared<CImage>(newPath, width, height);
    std::shared_ptr<IImage> imgAndHistory = std::make_shared<CImageAndHistory>(img, m_history);
    CDocumentItem item(imgAndHistory);
    ICommandPtr command = std::make_unique<InsertItemCommand>(m_items, item, position);
    m_history.AddAndExecuteCommand(move(command));
    return img;
}

size_t CDocument::GetItemsCount() const
{
    return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
    return m_items[index];
}

CDocumentItem CDocument::GetItem(size_t index)
{
    CheckPosForException(index);
    return m_items[index];
}

void CDocument::DeleteItem(size_t index)
{
    CheckPosForException(index);
    ICommandPtr command = std::make_unique<DeleteItemCommand>(m_items, index);
    m_history.AddAndExecuteCommand(move(command));
}

std::string CDocument::GetTitle() const
{
    return m_title;
}

void CDocument::SetTitle(const std::string& title)
{
    ICommandPtr command = std::make_unique<ChangeStringCommand>(m_title, title);
    m_history.AddAndExecuteCommand(move(command));
}

bool CDocument::CanUndo() const
{
    return m_history.CanUndo();
}

void CDocument::Undo()
{
    m_history.Undo();
}

bool CDocument::CanRedo() const
{
    return m_history.CanRedo();
}

void CDocument::Redo()
{
    m_history.Redo();
}

void CDocument::Save(const std::string& path) const
{    
    std::filesystem::path filePath(path);
    if (filePath.extension() != ".html")
        throw std::invalid_argument("extension of save file shoud be html");
    std::ofstream output(path);
    auto imagesDir = filePath.parent_path() / "images";
    if (!std::filesystem::exists(imagesDir))
        std::filesystem::create_directory(imagesDir);
    std::filesystem::copy(m_pathToTmpImagesDir, imagesDir);
    //std::filesystem::rename(filePath.parent_path() / m_pathToTmpImagesDir.stem(), 
    //    filePath.parent_path() / "images");
    //std::filesystem::remove_all(m_pathToTmpImagesDir);
    output << "<!DOCTYPE html>" << std::endl;
    output << "<html lang = \"ru\">" << std::endl;
    output << "<head>\n\t <meta charset = \"UTF - 8\">" << std::endl;
    output << "\t<title>" << m_title << "</title>" << std::endl;
    output << "<body>" << std::endl;
    for (size_t i = 0; i < GetItemsCount(); i++)
    {
        CConstDocumentItem item = GetItem(i);
        auto p = item.GetParagraph();
        if (p)
        {
            output << "\t<p>" << EncodeText(p->GetText()) << "</p>" << std::endl;
        }
        else
        {
            auto img = item.GetImage();
            output << "\t<img src = \"" << img->GetPath() << "\"" 
                << "width = \"" << img->GetWidth() << "\""
                << "height = \"" << img->GetHeight() << "\"" << " />";
        }
    }
    output << "</body\n</html>" << std::endl;
}

void CDocument::CheckPosForException(size_t pos)
{
    if (pos > m_items.size())
        throw std::invalid_argument("insertion position exceeds the number of items");
}

CDocument::~CDocument()
{
    if (std::filesystem::exists(m_pathToTmpImagesDir))
        std::filesystem::remove_all(m_pathToTmpImagesDir);
}
