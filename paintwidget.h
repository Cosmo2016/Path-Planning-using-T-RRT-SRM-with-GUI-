#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QMainWindow>
#include <QDebug>
#include <iostream>

#include "shape.h"
#include "ellipse.h"

using namespace std;

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    QPoint getStartPoint();
    QPoint getGoalPoint();
    QImage getQImage();

public slots:
    void setCurrentShape(const Shape::Code currentShape)
    {
        if(currentShape != this->currShapeCode_)
        {
            this->currShapeCode_ = currentShape;
        }
        /*if(pen != this->currPen_)
        {
            this->currPen_ = pen;
        }
        if(brush != this->currBrush_)
        {
            this->currBrush_ = brush;
        }*/
    }

    void saveFile()
    {
        cout<<"Save file"<<endl;
        QPixmap qPixmap;
        qPixmap = QWidget::grab();
        QImage qImage = qPixmap.toImage();

        // for test / sample
        /* QPoint qPoint(0, 50);
        QColor qColor(0, 0, 0);
        for (int i = 0; i < 100; ++i)
        {
            qImage.setPixelColor(qPoint, qColor);
            qPoint.setX(i);
        } */


        if (qImage.save("/Volumes/Cosmo/aaa.ppm", "PPM"))
        {
            // this->qPixmap(this->size());
            // this->render(&this->qPixmap);
            this->render(&qImage);
            cout<<"sava file success"<<endl;
        }
        else
        {
            cout<<"sava file fail"<<endl;
        }
    }

    void addPathPoint(QList<QPoint> pPoint)
    {
        this->path_.append(pPoint);
        this->repaint();
    }

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Shape::Code currShapeCode_;
    /*QPen currPen_;
    QBrush currBrush_;*/
    Shape *shape_;
    // bool perm;
    QList<Shape*> shapeList_;
    QList<QPoint> path_; // To save the planner's path result
    Ellipse *starPoint_ = NULL;
    Ellipse *goalPoint_ = NULL;
};

#endif // PAINTWIDGET_H
