#include "plan2deviroment.h"

Plan2DEviroment::Plan2DEviroment(PaintWidget *paintWidget)
{
    cout << "Plan2DEviroment::Plan2DEviroment" << endl;

    if (paintWidget == NULL) {
        cout << "error: paintWidget is null" << endl;
        return;
    }
    cout << "Start Point = " << paintWidget->getStartPoint().x()
         << "," << paintWidget->getStartPoint().y() << endl;
    cout << "Goal Point = "<< paintWidget->getGoalPoint().x()
         << "," << paintWidget->getGoalPoint().y() << endl;

    qImage_ = paintWidget->grab().toImage();
    auto space(std::make_shared<ob::RealVectorStateSpace>());
    space->addDimension(0.0, qImage_.height());
    space->addDimension(0.0, qImage_.width());
    cout << "qImage_.width() = " << qImage_.width() << endl;
    cout << "qImage_.height() = "<< qImage_.height() << endl;
    /*this->maxWidth_ = ppm_.getWidth() - 1;
    this->maxHeight_ = ppm_.getHeight() - 1;*/
    this->maxWidth_ = qImage_.height() - 1;
    this->maxHeight_ = qImage_.width() - 1;
    this->ss_ = std::make_shared<og::SimpleSetup>(space);

    // set state validity checking for this space
    this->ss_->setStateValidityChecker(
                [this](const ob::State *state) { return isStateValid(state); });
    space->setup();
    this->ss_->getSpaceInformation()->
            setStateValidityCheckingResolution(1.0 / space->getMaximumExtent());
    this->ss_->setPlanner(
                std::make_shared<og::RRTConnect>(this->ss_->getSpaceInformation()));

    connect(this, SIGNAL(sentPathPoint(QPoint)),
            paintWidget, SLOT(addPathPoint(QPoint)));
}


bool Plan2DEviroment::isStateValid(const ob::State *state) //const
{
    cout << "Plan2DEviroment::isStateValid" << endl;
    const int w = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[0], maxWidth_);
    const int h = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[1], maxHeight_);

    // const ompl::PPM::Color &c = ppm_.getPixel(h, w);
    // cout<<"w="<<w<<" h="<<h<<endl;
    const QColor c = this->qImage_.pixelColor(h, w);
    int *r = new int(-1);
    int *g = new int(-1);
    int *b = new int(-1);
    c.getRgb(r, g, b);
    // cout<<"r="<<*r<<", g="<<*g<<", b="<<*b<<endl;

    // return c.red() > 127 && c.green() > 127 && c.blue() > 127;
    bool ifValid = false;
    if (*r == 255 || *g == 255 || *b == 255) {
        // cout<<"Plan2DEviroment::isStateValid true"<<endl;
        ifValid = true;
    }
    delete r;
    delete g;
    delete b;
    return ifValid;
}

bool Plan2DEviroment::transactionTest()
{
    // here implement code ----------------!!!!!!!!!!!!!!!!!!!

    return false;
}

bool Plan2DEviroment::plan(unsigned int start_row, unsigned int start_col,
                           unsigned int goal_row, unsigned int goal_col)
{
    cout << "Plan2DEviroment::plan" << endl;
    if (!ss_)
        return false;

    // Create the termination condition
    double seconds = 5;
    ob::PlannerTerminationCondition ptc = ob::timedPlannerTerminationCondition( seconds, 0.1 );

    ob::ScopedState<> start(ss_->getStateSpace());
    start[0] = start_row;
    start[1] = start_col;
    ob::ScopedState<> goal(ss_->getStateSpace());
    goal[0] = goal_row;
    goal[1] = goal_col;
    ss_->setStartAndGoalStates(start, goal);

    // generate a few solutions; all will be added to the goal;
    for (int i = 0 ; i < 10 ; ++i) {
        // cout<<"generate a few solutions; all will be added to the goal "<<i<<endl;
        if (ss_->getPlanner())
            ss_->getPlanner()->clear();
        ss_->solve(ptc);
    }
    const std::size_t ns = ss_->getProblemDefinition()->getSolutionCount();
    OMPL_INFORM("Found %d solutions", (int)ns);
    if (ss_->haveSolutionPath()) {
        ss_->simplifySolution();
        og::PathGeometric &p = ss_->getSolutionPath();
        ss_->getPathSimplifier()->simplifyMax(p);
        ss_->getPathSimplifier()->smoothBSpline(p);
        return true;
    }

    return false;
}

QList<Point> Plan2DEviroment::recordSolution()
{
    cout << "Plan2DEviroment::recordSolution()" << endl;
    try {
        if (!ss_ || !ss_->haveSolutionPath())
            throw;
    } catch(...) {
        cout<<""<<endl;
    }

    og::PathGeometric p = ss_->getSolutionPath();
    p.interpolate();
    QList<Point> path;
    for (std::size_t i = 0 ; i < p.getStateCount() ; ++i) {
        const int w = std::min(maxWidth_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[0]);
        const int h = std::min(maxHeight_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[1]);
        //ompl::PPM::Color &c = ppm_.getPixel(h, w);
        //c.red = 255;
        //c.green = 0;
        //c.blue = 0;
        // QColor qColor(255, 0, 0);
        QPoint qPoint(h, w);
        Point pointOfPath;
        pointOfPath.setAPoint(qPoint);
        pointOfPath.setQBrush(QBrush(Qt::darkGreen));
        pointOfPath.setQPen(QPen(Qt::darkGreen));
        path << pointOfPath;
        // this->qImage_.setPixelColor(qPoint, qColor);
        // emit sentPathPoint(qPoint);

    }
    cout << "Plan2DEviroment::recordSolution() end" << endl;
    return path;
}

void Plan2DEviroment::save(const char *filename)
{
    cout << "Plan2DEviroment::save" << endl;
    if (!ss_) {
        std::cout<< "save NULL" << std::endl;
        return;
    }

    // ppm_.saveFile(filename);
    QString x("/Volumes/Cosmo/");
    this->qImage_.save(x.append(filename), "PPM");
}
