#include "plan2deviroment.h"
#include "utility.h"

Plan2DEviroment::Plan2DEviroment(PaintWidget *paintWidget)
{
    cout << "Plan2DEviroment::Plan2DEviroment" << endl;

    if (paintWidget == nullptr) {
        cout << "error: paintWidget is null" << endl;
        return;
    } else {
        this->paintWidget = paintWidget;
    }
    cout << "Start Point = " << this->paintWidget->getStartPoint().x()
         << "," << this->paintWidget->getStartPoint().y() << endl;
    cout << "Goal Point = "<< this->paintWidget->getGoalPoint().x()
         << "," << this->paintWidget->getGoalPoint().y() << endl;

    qImage_ = this->paintWidget->grab().toImage();

    auto space(std::make_shared<ob::RealVectorStateSpace>());
    space->addDimension(0.0, qImage_.height());
    space->addDimension(0.0, qImage_.width());

    cout << "qImage_.height() = "<< qImage_.height() << endl;
    cout << "qImage_.width() = " << qImage_.width() << endl;

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
}


bool Plan2DEviroment::isStateValid(const ob::State *state) //const
{
    cout << "Plan2DEviroment::isStateValid" << endl;
    const int w = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[0], maxWidth_);
    const int h = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[1], maxHeight_);

    // const ompl::PPM::Color &c = ppm_.getPixel(h, w);
    // cout << "w=" << w << " h=" << h << endl;
    const QColor c = this->qImage_.pixelColor(h, w);
    int *r = new int(-1);
    int *g = new int(-1);
    int *b = new int(-1);
    c.getRgb(r, g, b);
    // cout<<"r="<<*r<<", g="<<*g<<", b="<<*b<<endl;

    // return c.red() > 127 && c.green() > 127 && c.blue() > 127;
    bool ifValid = true;
    if (*r == 0 && *g == 0 && *b == 0) {
        // cout<<"Plan2DEviroment::isStateValid true"<<endl;
        ifValid = false;
    } else if (*r == 0 && *g == 255 && *b == 0) {
        ifValid = false;
    }

    if (ifValid) {
        Human *tmpHuman = this->paintWidget->getHuman();
        if (tmpHuman) {
            ifValid = this->transactionTest(tmpHuman->getAPoint().y(), tmpHuman->getAPoint().x(),
                                  120, h, w);
        }
    }

    delete r;
    delete g;
    delete b;
    return ifValid;
}

bool Plan2DEviroment::transactionTest(float man_x, float man_y, float man_diraction, float search_x, float search_y)
{
    // for debug
    cout << "Human x = " << man_x << endl;
    cout << "Human y = " << man_y << endl;
    cout << "Human dirction = " << man_diraction << endl;
    cout << "Search x = " << search_x <<  endl;
    cout << "Search y = " << search_y <<  endl;

    const float STD_DEV_1 = 3.5 * 500;
    const float STD_DEV_2 = 2 * 500;
    const float FF = 0.1;
    const float VN = 3;
    const float AMP = 1.0;
    const float MAX_DISTANTS = 25;

    float searcherAngleWithXAxis = Utility::pointAngleWithXAxis(search_x, search_y);
    float angle = searcherAngleWithXAxis - man_diraction;
    float distance = Utility::distanceBetween2Points(man_y, man_x, search_x, search_y);

    if (distance > 80) {
        return true;
    }

    float betaFront = 0;
    if (cos(angle) <= 0) {
        // Back
        cout << "Back" <<  endl;
        betaFront = pow(distance * cos(angle), 2) / (2 * pow(STD_DEV_1 / (1 + FF * VN), 2));
    } else {
        // Front
        cout << "Front" <<  endl;
        betaFront = pow(distance * cos(angle), 2) / (2 * pow(STD_DEV_1, 2));
    }

    float betaSide = pow(distance * sin(angle), 2) / (2 * pow(STD_DEV_2, 2));

    float beta = (betaFront + betaSide);
    cout << "beta = " << beta << endl;

    float p = pow(M_E, -beta) * AMP;
    cout << "p = " << p << endl;
    float radomP = Utility::randomProbability();
    cout << "radomP = " << radomP <<  endl;

    if (radomP < p) {
        return false;
    } else {
        return true;
    }
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
        cout << "" << endl;
    }

    og::PathGeometric p = ss_->getSolutionPath();
    p.interpolate();
    QList<Point> path; // Stor the trajectory
    for (std::size_t i = 0 ; i < p.getStateCount() ; ++i) {
        const int w = std::min(maxWidth_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[0]);
        const int h = std::min(maxHeight_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[1]);
        //ompl::PPM::Color &c = ppm_.getPixel(h, w);
        //c.red = 255;
        //c.green = 0;
        //c.blue = 0;
        // QColor qColor(255, 0, 0);
        Point pointOfPath;
        pointOfPath.setAPoint(QPoint(h, w));
        pointOfPath.setQBrushColor(Qt::blue);
        pointOfPath.setQPenColor(Qt::blue);
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
