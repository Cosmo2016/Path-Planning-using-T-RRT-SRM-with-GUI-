#include "plan2deviroment.h"

Plan2DEviroment::Plan2DEviroment(QImage qImage)
{
    qImage_ = qImage;
    auto space(std::make_shared<ob::RealVectorStateSpace>());
    space->addDimension(0.0, qImage.width());
    space->addDimension(0.0, qImage.height());
    /*this->maxWidth_ = ppm_.getWidth() - 1;
    this->maxHeight_ = ppm_.getHeight() - 1;*/
    this->maxWidth_ = qImage.width() - 1;
    this->maxHeight_ = qImage.height() - 1;
    this->ss_ = std::make_shared<og::SimpleSetup>(space);

    // set state validity checking for this space
    this->ss_->setStateValidityChecker(
                [this](const ob::State *state) { return isStateValid(state); });
    space->setup();
    this->ss_->getSpaceInformation()->
            setStateValidityCheckingResolution(1.0 / space->getMaximumExtent());
    this->ss_->setPlanner(
                std::make_shared<og::RRTConnect>(this->ss_->getSpaceInformation()));
}


bool Plan2DEviroment::isStateValid(const ob::State *state) //const
{
    const int w = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[0], maxWidth_);
    const int h = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[1], maxHeight_);

    // const ompl::PPM::Color &c = ppm_.getPixel(h, w);
    const QColor &c = this->qImage_.pixelColor(h, w);
    return c.red() > 127 && c.green() > 127 && c.blue() > 127;
}

bool Plan2DEviroment::plan(unsigned int start_row, unsigned int start_col,
                           unsigned int goal_row, unsigned int goal_col)
{
    if (!ss_)
        return false;
    ob::ScopedState<> start(ss_->getStateSpace());
    start[0] = start_row;
    start[1] = start_col;
    ob::ScopedState<> goal(ss_->getStateSpace());
    goal[0] = goal_row;
    goal[1] = goal_col;
    ss_->setStartAndGoalStates(start, goal);
    // generate a few solutions; all will be added to the goal;
    for (int i = 0 ; i < 10 ; ++i)
    {
        if (ss_->getPlanner())
            ss_->getPlanner()->clear();
        ss_->solve();
    }
    const std::size_t ns = ss_->getProblemDefinition()->getSolutionCount();
    OMPL_INFORM("Found %d solutions", (int)ns);
    if (ss_->haveSolutionPath())
    {
        ss_->simplifySolution();
        og::PathGeometric &p = ss_->getSolutionPath();
        ss_->getPathSimplifier()->simplifyMax(p);
        ss_->getPathSimplifier()->smoothBSpline(p);
        return true;
    }

    return false;
}


void Plan2DEviroment::recordSolution()
{
    if (!ss_ || !ss_->haveSolutionPath())
        return;
    og::PathGeometric &p = ss_->getSolutionPath();
    p.interpolate();
    for (std::size_t i = 0 ; i < p.getStateCount() ; ++i)
    {
        const int w = std::min(maxWidth_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[0]);
        const int h = std::min(maxHeight_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[1]);
        /* ompl::PPM::Color &c = ppm_.getPixel(h, w);
        c.red = 255;
        c.green = 0;
        c.blue = 0;*/
        QColor qColor(255, 0, 0);
        QPoint qPoint(h, w);
        this->qImage_.setPixelColor(qPoint, qColor);
    }
}

void Plan2DEviroment::save(const char *filename)
{
    if (!ss_)
    {
        std::cout<< "save NULL" << std::endl;
        return;
    }

    // ppm_.saveFile(filename);
    QString x("/Volumes/Cosmo/");
    this->qImage_.save(x.append(filename), "PPM");
}
