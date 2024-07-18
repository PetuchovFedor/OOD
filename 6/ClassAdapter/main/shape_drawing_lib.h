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

    class CTriangle : public ICanvasDrawable
    {
    public:
        CTriangle(const Point& p1, const Point& p2, const Point& p3)
            : m_vertex1(p1)
            , m_vertex2(p2)
            , m_vertex3(p3)
        {
        }
        void Draw(graphics_lib::ICanvas& canvas)const override
        {
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

    class CRectangle : public ICanvasDrawable
    {
    public:
        CRectangle(const Point& leftTop, int width, int height)
            : m_leftTop(leftTop)
        {
            if (width < 0 || height < 0)
                throw std::invalid_argument("width and heigh shoud be > 0");
            m_height = height;
            m_width = width;
        }
        void Draw(graphics_lib::ICanvas& canvas)const override
        {
            canvas.MoveTo(m_leftTop.x, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
            canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
            canvas.LineTo(m_leftTop.x, m_leftTop.y);
        }
    private:
        Point m_leftTop;
        int m_width, m_height;
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