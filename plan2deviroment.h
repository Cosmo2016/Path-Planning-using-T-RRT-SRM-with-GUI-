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
#include "human.h"


namespace ob = ompl::base;
namespace og = ompl::geometric;


class Plan2DEviroment : public QObject
{
    Q_OBJECT

public:
    Plan2DEviroment(QImage map);
    ~Plan2DEviroment();

    bool plan(unsigned int start_row, unsigned int start_col,
              unsigned int goal_row, unsigned int goal_col);
    QList<MyPoint> recordSolution();
    void save(const char *);

    QPointF* testHumanValidArea();

    // For debug switch
    bool isDebug_ = false;

    void setHuman(Human *);
    Human* getHuman() const;

private:
    bool isStateValid(const ob::State *);
    /*bool transactionTest(float man_x, float man_y,
                         float man_diraction, float search_x,
                         float search_y, float minDis, float maxDis);*/
    bool transactionTest(float, float) throw (std::exception);

    og::SimpleSetupPtr ss_;
    int maxWidth_;
    int maxHeight_;
    QImage map_;
    Human *human_ = nullptr;
};

#endif // PLAN2DEVIROMENT_H
