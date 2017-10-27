#include "paintwidget.h"
#include <iostream>

#include "line.h"
#include "rect.h"
#include "ellipse.h"

using namespace std;

PaintWidget::PaintWidget(QWidget *parent)
    : QWidget(parent), currShapeCode_(Shape::DepartPoint), shape(NULL), perm(false)
{
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    // QPaintEvent::registerEventType(8699);

}

void PaintWidget::paintEvent(QPaintEvent *event)
{
    /*if (event->type() == 8699)
    {
        QPainter painter(this);
        painter.drawPixmap(0, 0, this->size().height(), this->size().width(), qPixmap);
    }*/
    cout<<"PaintWidget::paintEvent"<<endl;
    QPainter painter(this);
    /*painter.setPen(Qt::red);
    painter.setBrush(Qt::black);*/
    // painter.drawRect(0, 0, size().width(), size().height());

    foreach(Shape *shape, shapeList)
    {
        shape->paint(painter);
    }
    if(shape)
    {
        shape->paint(painter);
    }
}

void PaintWidget::mousePressEvent(QMouseEvent *event)
{
    cout<<"PaintWidget::mousePressEvent"<<endl;
    QPainter painter(this);

    switch(this->currShapeCode_)
    {
        case Shape::DepartPoint:
        {
            shape = new Ellipse;
            shape->setQPen(QPen(Qt::black));
            shape->setQBrush(QBrush(Qt::red));
            break;
        }
        case Shape::DestPoint:
        {
            shape = new Ellipse;
            shape->setQPen(QPen(Qt::black));
            shape->setQBrush(QBrush(Qt::blue));
            break;
        }
        case Shape::Rect:
        {
            shape = new Rect;
            // shape->setQPen(Qt::blue);
            // shape->setQBrush(Qt::blue);
            break;
        }
    }
    if(shape != NULL)
    {
        perm = false;
        shapeList<<shape;
        shape->setStart(event->pos());
        shape->setEnd(event->pos());
    }
    this->repaint();
}

void PaintWidget::mouseMoveEvent(QMouseEvent *event)
{
    cout<<"PaintWidget::mouseMoveEvent"<<endl;
    if(shape && !perm)
    {
        if(this->currShapeCode_ == Shape::DepartPoint ||
                this->currShapeCode_ == Shape::DestPoint)
        {
            shape->setStart(event->pos());
        }
        else
        {
            shape->setEnd(event->pos());
        }
        // this->update();
        this->repaint();
    }
}

void PaintWidget::mouseReleaseEvent(QMouseEvent *event)
{
    cout<<"PaintWidget::mouseReleaseEvent"<<endl;
    perm = true;
}
