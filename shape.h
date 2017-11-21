#ifndef SHAPE_H
#define SHAPE_H

#include <QtGui>

class Shape
{
public:
    enum Code {
        DepartPoint,
        DestPoint,
        // Line,
        Rect,
        Person
    };

    Shape();
    virtual ~Shape();

    void setAPoint(const QPoint);
    QPoint getAPoint() const;

    void setBPoint(const QPoint);
    QPoint getBPoint() const;

    void setQBrushColor(const QColor);
    QBrush getQBurshColor() const;

    void setQPenColor(const QColor);
    QPen getQPenColor() const;

    void virtual paint(QPaintDevice*) = 0;

protected:
    QPoint aPoint_;
    QPoint bPoint_;

    QColor brushColor_;
    QColor penColor_;
};

#endif // SHAPE_H
