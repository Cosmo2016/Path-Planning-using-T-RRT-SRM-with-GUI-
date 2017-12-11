#include "human.h"
#include <random>
#include <cmath>
#include <utility.h>

Human::Human()
{
    this->id_ = Utility::randomRangeNumber(
                0, pow(2, sizeof(int) * 8 - 1) - 1);
    this->direction_ = -90;
    this->velocity_ = -1;
    this->minDistants_ = -1;
    this->maxDistants_ = -1;
    this->gender_ = Human::Gender_Unknown;
    this->relation_ = Human::Relation_Unknown;
    this->roughDistance_ = Human::RoughDistance_Unknown;
}

Human::Human(Human::Gender gender, Human::Relation relation, Human::RoughDistance roughDistance)
{
    this->gender_ = gender;
    this->relation_ = relation;
    this->roughDistance_ = roughDistance;
    this->updaeFuzzyRules();
}

Human::~Human()
{

}

void Human::setDirection(float angle) throw (std::invalid_argument)
{
    if (angle >= 0 && angle <= 360) {
        this->direction_ = angle - 90;
    } else {
        throw std::invalid_argument("Invalid input number, the angle's range is 0 ~ 360");
    }
}

double Human::getDirection() const
{
    return this->direction_ + 90;
}

void Human::setDirectionByRadian(float radian)
{
    this->direction_ = radian / M_PI * 180;
}

double Human::getsDirectionByRadian() const
{
    return this->direction_ / 180 * M_PI;
}

void Human::setVelocity(float velocity) throw (std::invalid_argument)
{
    if (velocity >= 0) {
        this->velocity_ = velocity;
    } else {
        throw std::invalid_argument("Invalid input number, the velocity's range should be >= 0");
    }
}

float Human::getVelocity() const
{
    return this->velocity_;
}

int Human::getHumanId() const
{
    return this->id_;
}

void Human::setMaxDistants(float maxDistants) throw (std::invalid_argument)
{
    if (maxDistants >= 0) {
        this->maxDistants_ = maxDistants;
    } else {
        throw std::invalid_argument("Invalid input number, the maxDistants' range should be >= 0");
    }
}

float Human::getMaxDistants() const
{
    return this->maxDistants_;
}

void Human::setMinDistants(float minDistants) throw (std::invalid_argument)
{
    if (minDistants >= 0) {
        this->minDistants_ = minDistants;
    } else {
        throw std::invalid_argument("Invalid input number, the minDistants' range should be >= 0");
    }
}

float Human::getMinDistants() const
{
    return this->minDistants_;
}

void Human::setGender(Human::Gender gender)
{
    this->gender_ = gender;
}

Human::Gender Human::getGender() const
{
    return this->gender_;
}

void Human::setRelation(Human::Relation relation)
{
    this->relation_ = relation;
}

Human::Relation Human::getRelation() const
{
    return this->relation_;
}

void Human::setRoughDistance(Human::RoughDistance roughDistance)
{
    this->roughDistance_ = roughDistance;
}

Human::RoughDistance Human::getRoughDistance() const
{
    return this->roughDistance_;
}

Human::SocialRelationArea Human::getSocialRelationArea()
{
    return this->socialRelationArea_;
}

void Human::paint(QPaintDevice *qWidget)
{
    QPainter painter(qWidget);

    const float ration = 2.5;

    painter.save();

    painter.translate(QPointF(aPoint_.x(), aPoint_.y()));

    // 反走样
    // painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));

    painter.rotate(this->direction_);

    // Notice: It has a central point adjustment.
    float ellipse_central_x = -this->minDistants_;
    float ellipse_central_y = -this->minDistants_ / ration;
    painter.drawEllipse(ellipse_central_x, ellipse_central_y,
                        this->minDistants_ * 2, this->minDistants_ * 2 / ration);

    // Direction
    painter.setPen(QPen(Qt::blue));
    painter.drawLine(QPoint(0, 0), QPoint(0, this->minDistants_ / ration));

    painter.restore();

    painter.setPen(QPen(Qt::blue));
    painter.drawEllipse(aPoint_, this->minDistants_ / ration, this->minDistants_ / ration);

    if(isGuidelineVisiable) {
        painter.setPen(QPen(Qt::yellow));
        painter.drawEllipse(aPoint_, maxDistants_, maxDistants_);
        painter.drawEllipse(aPoint_, minDistants_, minDistants_);
    }
}

void Human::updaeFuzzyRules()
{
    if (this->gender_ == Human::Gender_Male) {
        if (this->relation_ == Human::Relation_Familiar) {
            if (this->roughDistance_ == Human::RoughDistance_Near) {
                this->socialRelationArea_ = Human::SocialRelationArea_ClosePersonalArea;
            } else if (this->roughDistance_ == Human::RoughDistance_Far) {
                this->socialRelationArea_ = Human::SocialRelationArea_ClosePersonalArea;
            } else {
                this->socialRelationArea_ = Human::SocialRelationArea_Unknown;
            }
        } else if (this->relation_ == Human::Relation_Stranger) {
            if (this->roughDistance_ == Human::RoughDistance_Near) {
                this->socialRelationArea_ = Human::SocialRelationArea_SocialArea;
            } else if (this->roughDistance_ == Human::RoughDistance_Far) {
                this->socialRelationArea_ = Human::SocialRelationArea_NormalPersonalArea;
            } else {
                this->socialRelationArea_ = Human::SocialRelationArea_Unknown;
            }
        } else {
            this->socialRelationArea_ = Human::SocialRelationArea_Unknown;
        }
    } else if (this->gender_ == Human::Gender_Female) {
        if (this->relation_ == Human::Relation_Familiar) {
            if (this->roughDistance_ == Human::RoughDistance_Near) {
                this->socialRelationArea_ = Human::SocialRelationArea_NormalPersonalArea;
            } else if (this->roughDistance_ == Human::RoughDistance_Far) {
                this->socialRelationArea_ = Human::SocialRelationArea_ClosePersonalArea;
            } else {
                this->socialRelationArea_ = Human::SocialRelationArea_Unknown;
            }
        } else if (this->relation_ == Human::Relation_Stranger) {
            if (this->roughDistance_ == Human::RoughDistance_Near) {
                this->socialRelationArea_ = Human::SocialRelationArea_PublicArea;
            } else if (this->roughDistance_ == Human::RoughDistance_Far) {
                this->socialRelationArea_ = Human::SocialRelationArea_SocialArea;
            } else {
                this->socialRelationArea_ = Human::SocialRelationArea_Unknown;
            }
        } else {
            this->socialRelationArea_ = Human::SocialRelationArea_Unknown;
        }
    } else {
        this->socialRelationArea_ = Human::SocialRelationArea_Unknown;
    }

    // Or store this dates in database
    switch (this->socialRelationArea_) {
    case Human::SocialRelationArea_NormalPersonalArea:
        this->srmDeviation_.setSigma1(35);
        this->srmDeviation_.setSigma2(30);
        this->srmDeviation_.setVelocityDev(0.3);
        this->srmDeviation_.setProbabilityRatio(0.5);
        break;
    case Human::SocialRelationArea_ClosePersonalArea:
        // Add later
        break;
    case Human::SocialRelationArea_PublicArea:
        // Add later
        break;
    case Human::SocialRelationArea_SocialArea:
        // Add later
        break;
    default:
        // Add error later
        break;
    }
}

SRMDeviation Human::getFuzzyRule()
{
    return this->srmDeviation_;
}
