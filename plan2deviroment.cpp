#include "plan2deviroment.h"
#include "utility.h"
#include "srmdeviation.h"

Plan2DEviroment::Plan2DEviroment(QImage map)
{
    cout << "Plan2DEviroment::Plan2DEviroment()" << endl;

    this->map_ = map;

    auto space(std::make_shared<ob::RealVectorStateSpace>());
    space->addDimension(0.0, this->map_.height());
    space->addDimension(0.0, this->map_.width());

    this->maxWidth_ = this->map_.height() - 1;
    this->maxHeight_ = this->map_.width() - 1;

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

Plan2DEviroment::~Plan2DEviroment()
{
    // !!!Pls do not delete Humans here
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
    ob::PlannerTerminationCondition ptc = ob::timedPlannerTerminationCondition(seconds, 0.1);

    ob::ScopedState<> start(ss_->getStateSpace());
    start[0] = start_col;
    start[1] = start_row;

    ob::ScopedState<> goal(ss_->getStateSpace());
    goal[0] = goal_col;
    goal[1] = goal_row;
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
        cout << "No SolutionPath be found" << endl;
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
        MyPoint pointOfPath;
        pointOfPath.setAPoint(QPoint(h, w));
        pointOfPath.setQBrushColor(Qt::blue);
        pointOfPath.setQPenColor(Qt::blue);
        path << pointOfPath;

    }
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
    this->map_.save(x.append(filename), "PPM");
}

QPointF* Plan2DEviroment::testHumanValidArea()
{
    bool ifValid = true;

    /*Human *tmpHuman = this->paintWidget->getHuman();
    tmpHuman->setDirection(30);*/

    float randomX = -1;
    float randomY = -1;
    const float radius = 150.0;

    if (this->human_) {
        // Human *human_ = this->paintWidget->getHuman();

        float xMin = this->human_->getAPoint().x() - radius;
        if (xMin < 0) {
            xMin = 0;
        }
        float xMax = this->human_->getAPoint().x() + radius;
        if (xMax >= maxHeight_) {
            xMax = maxHeight_ - 1;
        }

        float yMin = this->human_->getAPoint().y() - radius;
        if (yMin < 0) {
            yMin = 0;
        }
        float yMax = this->human_->getAPoint().y() + radius;
        if (yMax >= maxWidth_) {
            yMax = maxWidth_ - 1;
        }

        randomX = Utility::randomRangeNumber(xMin, xMax);
        randomY = Utility::randomRangeNumber(yMin, yMax);

        if (this->human_) {
            ifValid = this->transactionTest(randomX, randomY);
        }

    }

    if (ifValid == true) {
        return new QPointF(randomX, randomY);
    } else {
        // cout << "give up" << endl;
        return nullptr;
    }
}

bool Plan2DEviroment::isStateValid(const ob::State *state) //const
{
    // cout << "Plan2DEviroment::isStateValid()" << endl;
    const int w = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[0], maxWidth_);
    const int h = std::min((int)state->as
                           <ob::RealVectorStateSpace::StateType>()->values[1], maxHeight_);

    // const ompl::PPM::Color &c = ppm_.getPixel(h, w);
    const QColor c = this->map_.pixelColor(h, w);
    int *r = new int(-1);
    int *g = new int(-1);
    int *b = new int(-1);
    c.getRgb(r, g, b);

    // return c.red() > 127 && c.green() > 127 && c.blue() > 127;
    bool ifValid = true;
    if (*r == 0 && *g == 0 && *b == 0) { // Black refer to abstacles
        // cout<<"Plan2DEviroment::isStateValid true"<<endl;
        ifValid = false;
    }

    if (ifValid) {
        if (this->human_) {
            ifValid = this->transactionTest(h, w);
        }
    }

    delete r;
    delete g;
    delete b;
    return ifValid;
}

bool Plan2DEviroment::transactionTest(float searchX, float searchY) throw (std::exception)
{
    // cout << "Plan2DEviroment::transactionTest()" << endl;
    /*if (searchX < 0 || searchX >= this->maxHeight_
            || searchY < 0 || searchY >= this->maxWidth_) {
        throw std::invalid_argument("Invalid coordinate point");
    }*/
    if (!this->human_) {
        throw std::runtime_error("No human to be found");
    }

    float searcherAngleWithXAxis = Utility::getIncludedAngle(this->human_->getAPoint().x(),
                                                             this->human_->getAPoint().y(),
                                                             searchX, searchY);
    float includedAngle = searcherAngleWithXAxis - this->human_->getsDirectionByRadian();
    float distance = Utility::distanceBetween2Points(this->human_->getAPoint().x(),
                                                     this->human_->getAPoint().y(),
                                                     searchX, searchY);

    SRMDeviation srmDeviation = this->human_->getFuzzyRule();

    if (!srmDeviation.isEmpty()) {
        if (distance < this->human_->getMinDistants()) {
            return false;
        } else if(distance > this->human_->getMinDistants() &&
                  distance < this->human_->getMaxDistants()) {
            // Between min and max distances
            float betaFront = 0;
            // if (cos(includedAngle / 180 * M_PI) <= 0) {
            if (cos(includedAngle) <= 0) {
                // cout << "Back" <<  endl;
                // betaFront = pow(distance * cos(includedAngle), 2) / (2 * pow(STD_DEV_1 / (1 + FF * VN), 2));
                betaFront = pow(distance * cos(includedAngle), 2) / (2 * pow(srmDeviation.getSigma2(), 2));
            } else {
                // cout << "Front" <<  endl;
                betaFront = pow(distance * cos(includedAngle), 2) /
                        (2 * pow(srmDeviation.getSigma1() /
                        (1 + srmDeviation.getVelocityDev() * this->human_->getVelocity()), 2));
            }
            float betaSide = pow(distance * sin(includedAngle), 2) / (2 * pow(srmDeviation.getSigma1(), 2));

            float beta = (betaFront + betaSide);
            float p = pow(M_E, -beta * srmDeviation.getProbabilityRatio()) ;
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
}

void Plan2DEviroment::setHuman(Human *human)
{
    this->human_ = human;
}
Human* Plan2DEviroment::getHuman() const
{
    return this->human_;
}
