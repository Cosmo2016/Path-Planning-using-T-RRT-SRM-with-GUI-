#ifndef PLAN2DEVIROMENT_H
#define PLAN2DEVIROMENT_H

#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/RRTstar.h>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <ompl/util/PPM.h>
#include <ompl/config.h>

#include <boost/filesystem.hpp>
#include "paintwidget.h"


namespace ob = ompl::base;
namespace og = ompl::geometric;


class Plan2DEviroment : public QObject
{
    Q_OBJECT

public:
    Plan2DEviroment(PaintWidget *paintWidget) ;
    bool plan(unsigned int start_row, unsigned int start_col,
              unsigned int goal_row, unsigned int goal_col);
    QList<Point> recordSolution();
    void save(const char *);
    bool isDebug = true;

private:
    bool isStateValid(const ob::State *);
    // Kernel implement here!!!
    bool transactionTest(float man_x, float man_y,
                         float man_diraction, float search_x,
                         float search_y, float minDis, float maxDis);
    og::SimpleSetupPtr ss_;
    int maxWidth_;
    int maxHeight_;
    QImage qImage_;

    PaintWidget *paintWidget = nullptr;
};

#endif // PLAN2DEVIROMENT_H
