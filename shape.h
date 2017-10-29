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
        this->startPoint_ = s;
    }

    void setEnd(QPoint e) {
        this->endPoint_ = e;
    }

    QPoint startPoint() {
        return this->startPoint_;
    }

    QPoint endPoint() {
        return this->endPoint_;
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
    QPoint startPoint_;
    QPoint endPoint_;

    QBrush qBrush_;
    QPen qPen_;
};

#endif // SHAPE_H
