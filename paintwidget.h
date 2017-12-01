#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QMainWindow>

#include "shape.h"
#include "ellipse.h"
#include "point.h"
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
    QImage getQImage();
    Human* getHuman();

public slots:
    void setCurrentShape(const Shape::Code currentShape);
    void save2File();
    void addPathPoint(QList<Point> &pPoint);

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);

private:
    Shape::Code currShapeCode_;
    Shape *shape_;

    QList<Shape*> obstacleList_; // Store the obstacles posision.
    QList<Point> path_; // To save the planner's path result.
    Ellipse *starPoint_ = NULL;
    Ellipse *goalPoint_ = NULL;
    Human *person_; // For current demo version, we only have 1 person.
};

#endif // PAINTWIDGET_H
