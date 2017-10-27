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
        Rect
    };

    Shape();

    void setStart(QPoint s) {
        start = s;
    }

    void setEnd(QPoint e) {
        end = e;
    }

    QPoint startPoint() {
        return start;
    }

    QPoint endPoint() {
        return end;
    }

    void setQBrush(const QBrush &qBrush)
    {
        this->qBrush_ = qBrush;
    }

    QBrush getQBursh() const
    {
        return this->qBrush_;
    }

    void setQPen(const QPen &qPen)
    {
        this->qPen_ = qPen;
    }

    QPen getQPen() const
    {
        return this->qPen_;
    }

    void virtual paint(QPainter & painter) = 0;

protected:
    QPoint start;
    QPoint end;

    QBrush qBrush_;
    QPen qPen_;
};

#endif // SHAPE_H
