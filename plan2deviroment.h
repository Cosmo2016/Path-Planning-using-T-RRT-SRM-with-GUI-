#ifndef PLAN2DEVIROMENT_H
#define PLAN2DEVIROMENT_H

#include <ompl/base/spaces/RealVectorStateSpace.h>
#include <ompl/geometric/SimpleSetup.h>
#include <ompl/geometric/planners/rrt/RRTstar.h>
#include <ompl/geometric/planners/rrt/RRTConnect.h>
#include <ompl/util/PPM.h>
#include <ompl/config.h>
#include <QImage>

#include <boost/filesystem.hpp>
#include <iostream>

namespace ob = ompl::base;
namespace og = ompl::geometric;


class Plan2DEviroment
{
public:
    Plan2DEviroment(QImage);
    bool plan(unsigned int start_row, unsigned int start_col, unsigned int goal_row, unsigned int goal_col);
    void recordSolution();
    void save(const char *filename);

private:
    bool isStateValid(const ob::State *state);
    og::SimpleSetupPtr ss_;
    int maxWidth_;
    int maxHeight_;
    QImage qImage_;
};

#endif // PLAN2DEVIROMENT_H
