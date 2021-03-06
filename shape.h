#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>

class Shape
{
public:
    enum Code {
        DepartPoint,
        DestPoint,
        Rect,
        Person
    };

    Shape();
    virtual ~Shape();

    void setAPoint(const QPointF);
    QPointF getAPoint() const;

    void setBPoint(const QPointF);
    QPointF getBPoint() const;

    void setQBrushColor(const QColor);
    QBrush getQBurshColor() const;

    void setQPenColor(const QColor);
    QPen getQPenColor() const;

    void virtual paint(QPaintDevice*) = 0;

protected:
    QPointF aPoint_;
    QPointF bPoint_;

    QColor brushColor_;
    QColor penColor_;
};

#endif // SHAPE_H
