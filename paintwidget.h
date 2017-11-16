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
    void setCurrentShape(const Shape::Code currentShape);
    void saveFile();
    void addPathPoint(QList<QPoint> pPoint);

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
