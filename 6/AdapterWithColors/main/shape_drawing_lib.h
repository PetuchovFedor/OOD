#pragma once
#include "graphics_lib.h"

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
    struct Point
    {
        int x;
        int y;
    };

    // Интерфейс объектов, которые могут быть нарисованы на холсте из graphics\_lib
    class ICanvasDrawable
    {
    public:
        virtual void Draw(graphics_lib::ICanvas& canvas)const = 0;
        virtual ~ICanvasDrawable() = default;
    };

    class CShape : public ICanvasDrawable
    {
    public:
        CShape(uint32_t color)
            : m_color(color)
        {}

        uint32_t GetColor() const
        {
            return m_color;
        }

    private:
        uint32_t m_color;
    };

    class CTriangle : public CShape
    {
    public:
        CTriangle(const Point& p1, const Point& p2, const Point& p3,
            uint32_t color)
            : m_vertex1(p1)
            , m_vertex2(p2)
            , m_vertex3(p3)
            , CShape(color)
        {
        }
        void Draw(graphics_lib::ICanvas& canvas)const override
        {
            canvas.SetColor(CShape::GetColor());
            canvas.MoveTo(m_vertex1.x, m_vertex1.y);
            canvas.LineTo(m_vertex2.x, m_vertex2.y);
            canvas.LineTo(m_vertex3.x, m_vertex3.y);
            canvas.LineTo(m_vertex1.x, m_vertex1.y);
        }
    private:
        Point m_vertex1;
        Point m_vertex2;
        Point m_vertex3;
    };

    class CRectangle : public CShape
    {
    public:
        CRectangle(const Point& leftTop, int width, int height,
            uint32_t color)
            : m_leftTop(leftTop)
            , CShape(color)
        {
            if (width < 0 || height < 0)
                throw std::invalid_argument("width and heigh shoud be > 0");
            m_height = height;
            m_width = width;
        }
        void Draw(graphics_lib::ICanvas& canvas)const override
        {
            canvas.SetColor(CShape::GetColor());
            canvas.MoveTo(m_leftTop.x, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y);
        }
    private:
        Point m_leftTop;
        size_t m_width, m_height;
    };

    // Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
    class CCanvasPainter
    {
    public:
        CCanvasPainter(graphics_lib::ICanvas& canvas)
            :m_canvas(canvas)
        {
        }
        void Draw(const ICanvasDrawable& drawable)
        {
            drawable.Draw(m_canvas);
        }
    private:
        graphics_lib::ICanvas& m_canvas;
    };
}