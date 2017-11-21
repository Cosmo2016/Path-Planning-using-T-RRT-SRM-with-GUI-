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

    void setQBrush(const QBrush);
    QBrush getQBursh() const;

    void setQPen(const QPen&);
    QPen getQPen() const;

    void virtual paint(QPaintDevice*) = 0;

protected:
    QPoint aPoint_;
    QPoint bPoint_;

    QBrush qBrush_;
    QPen qPen_;
};

#endif // SHAPE_H
