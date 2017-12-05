#include "plan2deviroment.h"
#include "utility.h"

Plan2DEviroment::Plan2DEviroment(PaintWidget *paintWidget)
{
    cout << "Plan2DEviroment::Plan2DEviroment()" << endl;

    if (paintWidget == nullptr) {
        cout << "error: paintWidget is null" << endl;
        return;
    } else {
        this->paintWidget = paintWidget;
    }

    if (isDebug_) {
        cout << "Start Point = " << this->paintWidget->getStartPoint().x()
             << "," << this->paintWidget->getStartPoint().y() << endl;
        cout << "Goal Point = "<< this->paintWidget->getGoalPoint().x()
             << "," << this->paintWidget->getGoalPoint().y() << endl;
    }

    qImage_ = this->paintWidget->grab().toImage();

    auto space(std::make_shared<ob::RealVectorStateSpace>());
    space->addDimension(0.0, qImage_.height());
    space->addDimension(0.0, qImage_.width());

    if (isDebug_) {
        cout << "qImage_.height() = "<< qImage_.height() << endl;
        cout << "qImage_.width() = " << qImage_.width() << endl;
    }

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
    // cout << "Plan2DEviroment::isStateValid()" << endl;
    const int w = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[0], maxWidth_);
    const int h = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[1], maxHeight_);

    // const ompl::PPM::Color &c = ppm_.getPixel(h, w);
    const QColor c = this->qImage_.pixelColor(h, w);
    int *r = new int(-1);
    int *g = new int(-1);
    int *b = new int(-1);
    c.getRgb(r, g, b);

    // return c.red() > 127 && c.green() > 127 && c.blue() > 127;
    bool ifValid = true;
    if (*r == 0 && *g == 0 && *b == 0) { // Black
        // cout<<"Plan2DEviroment::isStateValid true"<<endl;
        ifValid = false;
    }

    if (ifValid) {
        Human *tmpHuman = this->paintWidget->getHuman();
        if (tmpHuman) {
            ifValid = this->transactionTest(tmpHuman->getAPoint().x(), tmpHuman->getAPoint().y(),
                                  tmpHuman->getDirection(), h, w, tmpHuman->getMinDistants(), tmpHuman->getMaxDistants());
        }
    }

    delete r;
    delete g;
    delete b;
    return ifValid;
}

bool Plan2DEviroment::transactionTest(float man_x, float man_y,
                                      float man_diraction, float search_x,
                                      float search_y, float minDis, float maxDis)
{
    // cout << "Plan2DEviroment::transactionTest()" << endl;

    if (isDebug_) {
        cout << "Human x = " << man_x << endl;
        cout << "Human y = " << man_y << endl;
        cout << "Human dirction = " << man_diraction << endl;
        cout << "Search x = " << search_x <<  endl;
        cout << "Search y = " << search_y <<  endl;
    }

    const float STD_DEV_1 = 35;
    const float STD_DEV_2 = 30;
    const float FF = 0.3;
    const float VN = 6;
    const float AMP = 0.5;

    // float searcherAngleWithXAxis = Utility::pointAngleWithXAxis(search_x, search_y);
    float searcherAngleWithXAxis = Utility::getIncludedAngle(man_x, man_y, search_x, search_y);
    float includedAngle = searcherAngleWithXAxis - man_diraction;
    float distance = Utility::distanceBetween2Points(man_x, man_y, search_x, search_y);

    if (distance < minDis) {
        return false;
    } else if(distance > minDis && distance < maxDis) {
        // Between min and max distances
        float betaFront = 0;
        if (cos(includedAngle / 180 * M_PI) <= 0) {
            // cout << "Back" <<  endl;
            betaFront = pow(distance * cos(includedAngle / 180 * M_PI), 2) / (2 * pow(STD_DEV_1 / (1 + FF * VN), 2));
            // betaFront = distance * pow(cos(angle), 2) / (2 * pow(STD_DEV_1 / (1 + FF * VN), 2));

        } else {
            // cout << "Front" <<  endl;
            betaFront = pow(distance * cos(includedAngle / 180 * M_PI), 2) / (2 * pow(STD_DEV_1, 2));
            // betaFront = distance * pow(cos(angle), 2) / (2 * pow(STD_DEV_1, 2));
        }

        float betaSide = pow(distance * sin(includedAngle / 180 * M_PI), 2) / (2 * pow(STD_DEV_2, 2));
        float beta = (betaFront + betaSide);

        float p = pow(M_E, -beta * AMP) ;
        float radomP = Utility::randomProbability();
        if (radomP < p) {
            return false;
        } else {
            return true;
        }
    } else {
        return true;
    }
}

bool Plan2DEviroment::plan(unsigned int start_row, unsigned int start_col,
                           unsigned int goal_row, unsigned int goal_col)
{
    cout << "Plan2DEviroment::plan()" << endl;
    if (!ss_) {
        return false;
    }
    // Create the termination condition
    double seconds = 15;
    ob::PlannerTerminationCondition ptc = ob::timedPlannerTerminationCondition( seconds, 0.1 );

    ob::ScopedState<> start(ss_->getStateSpace());
    start[0] = start_row;
    start[1] = start_col;
    ob::ScopedState<> goal(ss_->getStateSpace());
    goal[0] = goal_row;
    goal[1] = goal_col;
    ss_->setStartAndGoalStates(start, goal);

    // Generate a few solutions; all will be added to the goal;
    for (int i = 0 ; i < 10 ; ++i) {
        // cout << "generate a few solutions; all will be added to the goal " << i << endl;
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

QList<MyPoint> Plan2DEviroment::recordSolution()
{
    // cout << "Plan2DEviroment::recordSolution()" << endl;
    try {
        if (!ss_ || !ss_->haveSolutionPath())
            throw;
    } catch(...) {
        cout << "lan2DEviroment::recordSolution() error" << endl;
    }

    og::PathGeometric p = ss_->getSolutionPath();
    p.interpolate();
    QList<MyPoint> path; // Store the trajectory
    for (std::size_t i = 0 ; i < p.getStateCount() ; ++i) {
        const int w = std::min(maxWidth_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[0]);
        const int h = std::min(maxHeight_, (int)p.getState(i)->as<ob::RealVectorStateSpace::StateType>()->values[1]);
        //ompl::PPM::Color &c = ppm_.getPixel(h, w);
        //c.red = 255;
        //c.green = 0;
        //c.blue = 0;
        // QColor qColor(255, 0, 0);
        MyPoint pointOfPath;
        pointOfPath.setAPoint(QPoint(h, w));
        pointOfPath.setQBrushColor(Qt::blue);
        pointOfPath.setQPenColor(Qt::blue);
        path << pointOfPath;
        // this->qImage_.setPixelColor(qPoint, qColor);
        // emit sentPathPoint(qPoint);

    }
    // cout << "Plan2DEviroment::recordSolution() end" << endl;
    return path;
}

void Plan2DEviroment::save(const char *filename)
{
    cout << "Plan2DEviroment::save()" << endl;
    if (!ss_) {
        std::cout<< "save NULL" << std::endl;
        return;
    }

    // ppm_.saveFile(filename);
    QString x("/Volumes/Cosmo/");
    this->qImage_.save(x.append(filename), "PPM");
}

QPointF* Plan2DEviroment::testHumanValidArea()
{
    bool ifValid = true;

    Human *tmpHuman = this->paintWidget->getHuman();
    tmpHuman->setDirection(30);

    float randomX = -1;
    float randomY = -1;
    const float radius = 150.0;

    if (tmpHuman) {
        Human *tmpHuman = this->paintWidget->getHuman();

        float xMin = tmpHuman->getAPoint().x() - radius;
        if (xMin < 0) {
            xMin = 0;
        }
        float xMax = tmpHuman->getAPoint().x() + radius;
        if (xMax >= maxHeight_) {
            xMax = maxHeight_ - 1;
        }

        float yMin = tmpHuman->getAPoint().y() - radius;
        if (yMin < 0) {
            yMin = 0;
        }
        float yMax = tmpHuman->getAPoint().y() + radius;
        if (yMax >= maxWidth_) {
            yMax = maxWidth_ - 1;
        }


        // int randomW = Utility::randomRangeNumber(0, maxWidth_ - 1);
        // int randomH = Utility::randomRangeNumber(0, maxHeight_ - 1);
        randomX = Utility::randomRangeNumber(xMin, xMax);
        randomY = Utility::randomRangeNumber(yMin, yMax);

        if (tmpHuman) {
            ifValid = this->transactionTest(tmpHuman->getAPoint().x(), tmpHuman->getAPoint().y(),
                                  tmpHuman->getDirection(), randomX, randomY, tmpHuman->getMinDistants(), tmpHuman->getMaxDistants());
        }

    }

    if (ifValid == true) {
        return new QPointF(randomX, randomY);
    } else {
        // cout << "give up" << endl;
        return nullptr;
    }
}
