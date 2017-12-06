#ifndef HUMAN_H
#define HUMAN_H

#include "shape.h"
#include "srmdeviation.h"

class Human : public Shape
{
public:

    enum Status {
        Status_None,
        Status_Move,
        Status_Fixed,
        Status_Rotate
    };

    enum Event {
        Event_DownClick,
        Event_UpClick,
    };

    enum Gender {
        Gender_Unknown,
        Gender_Male,
        Gender_Female
    };

    enum Relation {
        Relation_Unknown,
        Relation_Familiar,
        Relation_Stranger
    };

    enum RoughDistance {
        RoughDistance_Unknown,
        RoughDistance_Near,
        RoughDistance_Far
    };

    enum SocialRelationArea {
        SocialRelationArea_Unknown,
        SocialRelationArea_NormalPersonalArea,
        SocialRelationArea_ClosePersonalArea,
        SocialRelationArea_SocialArea,
        SocialRelationArea_PublicArea,
    };

    Human();
    Human(Human::Gender, Human::Relation, Human::RoughDistance);
    ~Human();

    void setDirection(float);
    double getDirection() const;

    int getHumanId() const;

    float getMaxDistants() const;
    float getMinDistants() const;

    Human::Gender getGender() const;

    void setRelation(Human::Relation);
    Human::Relation getRelation() const;

    void setRoughDistance(Human::RoughDistance);
    Human::RoughDistance getRoughDistance() const;

    Human::SocialRelationArea getsocialRelationArea();

    void paint(QPaintDevice *) override;

    bool isGuidelineVisiable = true;
    bool ifDebug = false;

private:
    int id_;
    float direction_;
    float velocity_;
    float minDistants_;
    float maxDistants_;
    Human::Gender gender_;
    Human::Relation relation_;
    Human::RoughDistance roughDistance_;
    Human::SocialRelationArea socialRelationArea_;
    SRMDeviation srmDeviation_;

    void updaeFuzzyRules();
    SRMDeviation getFuzzyRule();
};

#endif // HUMAN_H
