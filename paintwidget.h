#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QMainWindow>

#include "shape.h"
#include "ellipse.h"
#include "mypoint.h"
#include "human.h"

using namespace std;

class PaintWidget : public QWidget
{
    Q_OBJECT

public:
    PaintWidget(QWidget *parent = 0);
    ~PaintWidget();

    QPoint getStartPoint();
    QPoint getGoalPoint();
    QImage getMap();
    Human* getHuman() const;

    void add2PathList(QList<MyPoint> &pPoint);
    void clearPathList();

    void addValidPointList4Test(QList<MyPoint>&);
    void clearValidPointList4Test();

public slots:
    void setCurrentShape(const Shape::Code currentShape);
    void save2File();

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Shape::Code currShapeCode_;
    Shape *shape_;

    QList<Shape*> obstacleList_; // Store the obstacles posision.
    QList<MyPoint> path_; // To save the planner's path result.
    QList<MyPoint> validPointList4Test_; // To save test valid Point
    Ellipse *starPoint_ = nullptr;
    Ellipse *goalPoint_ = nullptr;
    Human *human_ = nullptr; // For current demo version, we only have 1 person.
};

#endif // PAINTWIDGET_H
