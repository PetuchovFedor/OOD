#pragma once
#include <cstdint>
#include <iostream>
#include <iomanip>
#include <sstream>

namespace graphics_lib
{
    std::string TransformUint32_tToHex(uint32_t color)
    {
        std::stringstream stream;
        //stream << 
        stream << std::format("{:#08x}", color);
        auto result = stream.str();
        result.erase(result.begin());
        result.erase(result.begin());
       //stream /*<< std::setfill('0') << std::setw(sizeof(uint32_t) * 2)*/<< std::hex << color;
        return result;
    }
    // ����� ��� ���������
    class ICanvas
    {
    public:
        // ��������� ����� � ������� 0xRRGGBB
        virtual void SetColor(uint32_t rgbColor) = 0;
        virtual void MoveTo(int x, int y) = 0;
        virtual void LineTo(int x, int y) = 0;
        virtual ~ICanvas() = default;
    };

    // ���������� ������ ��� ���������
    class CCanvas : public ICanvas
    {
    public:
        void SetColor(uint32_t rgbColor) override
        {
            std::cout << '#' << TransformUint32_tToHex(rgbColor) << std::endl;
            // TODO: ������� � output ���� � ���� ������ SetColor (#RRGGBB)
        }
        void MoveTo(int x, int y) override
        {
            std::cout << "MoveTo (" << x << ", " << y << ")" << std::endl;
        }
        void LineTo(int x, int y) override
        {
            std::cout << "LineTo (" << x << ", " << y << ")" << std::endl;
        }
    };
}