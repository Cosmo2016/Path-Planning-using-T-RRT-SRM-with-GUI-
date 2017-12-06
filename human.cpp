#include "human.h"
#include <random>
#include <cmath>
#include <utility.h>

Human::Human()
{
    this->id_ = Utility::randomRangeNumber(
                0, pow(2, sizeof(int) * 8 - 1) - 1);
    this->setDirection(0);
    this->velocity_ = 0;
    this->minDistants_ = 25.0;
    this->maxDistants_ = 80.0;
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

void Human::setDirection(float angle)
{
    if (angle >= 0 && angle <= 360) {
        this->direction_ = angle - 90;
    } else {
        // throw exception
    }
}

double Human::getDirection() const
{
    return this->direction_ + 90;
}

int Human::getHumanId() const
{
    return this->id_;
}

float Human::getMaxDistants() const
{
    return this->maxDistants_;
}

float Human::getMinDistants() const
{
    return this->minDistants_;
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

Human::SocialRelationArea Human::getsocialRelationArea()
{
    return this->socialRelationArea_;
}

void Human::paint(QPaintDevice *qWidget)
{
    QPainter painter(qWidget);

    const int ellipseWidth = 50;
    const int ellipseHeight = 20;

    painter.save();

    painter.translate(QPointF(aPoint_.x(), aPoint_.y()));

    // 反走样
    // painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setBrush(QBrush(this->getQBurshColor()));
    painter.setPen(QPen(this->getQPenColor()));

    painter.rotate(this->direction_);

    // Notice: It has a central point adjustment.
    float ellipse_central_x = -ellipseWidth / 2.0;
    float ellipse_central_y = -ellipseHeight / 2.0;
    painter.drawEllipse(ellipse_central_x, ellipse_central_y,
                        ellipseWidth, ellipseHeight);

    // Direction
    painter.setPen(QPen(Qt::blue));
    painter.drawLine(QPoint(0, 0), QPoint(0, 10));

    painter.restore();

    painter.setPen(QPen(Qt::blue));
    painter.drawEllipse(aPoint_, 10, 10);

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

    // Other condition will be added later
    default:
        break;
    }
}

SRMDeviation Human::getFuzzyRule()
{

    return this->srmDeviation_;

}
