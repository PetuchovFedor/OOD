#pragma once
#include <iostream>
#include <string>
#include "Geom.h"
#include "CoW.h"
#include "Tile.h"

class Image
{
public:
    /**
     * Конструирует изображение заданного размера. Если размеры не являются положительными,
     * выбрасывает исключение std::out_of_range.
     */
    explicit Image(Size size, char color = ' ');

    // Возвращает размер изображения в пикселях.
    Size GetSize() const noexcept;

    /**
     * Возвращает «цвет» пикселя в указанных координатах.Если координаты выходят за пределы
     * изображения, возвращает «пробел».
     */
    char GetPixel(Point p) const noexcept;

    /**
     * Задаёт «цвет» пикселя в указанных координатах. Если координаты выходят за пределы изображения
     * действие игнорируется.
     */
    void SetPixel(Point p, char color);

private:
    struct TileWithCoord
    {
        TileWithCoord(Point leftTop, const CoW<Tile>& tile)
            : leftTop(leftTop)
            , tile(tile)
        {}
        Point leftTop;
        CoW<Tile> tile;
    };
    std::vector<TileWithCoord> m_tiles;
    Size m_size;
};

/**
 * Выводит в поток out изображение в виде символов.
 */
void Print(const Image& img, std::ostream& out);

/**
 * Загружает изображение из pixels. Линии изображения разделяются символами \n.
 * Размеры картинки определяются по количеству переводов строки и самой длинной линии.
 */
Image LoadImage(const std::string& pixels);