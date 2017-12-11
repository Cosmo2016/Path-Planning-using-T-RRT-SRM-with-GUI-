#ifndef HUMAN_H
#define HUMAN_H

#include <exception>
#include "shape.h"
#include "srmdeviation.h"

class Human : public Shape
{
public:
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

    void setDirection(float) throw (std::invalid_argument);
    float getDirection() const;
    void setDirectionByRadian(float);
    float getsDirectionByRadian() const;

    void setDirectionOffset(float);
    float getDirectionOffset() const;
    void setDirectionOffsetByRadian(float);
    float getDirectionOffsetByRadian() const;


    void setVelocity(float) throw (std::invalid_argument);
    float getVelocity() const;

    int getHumanId() const;

    void setMaxDistants(float) throw (std::invalid_argument);
    float getMaxDistants() const;

    void setMinDistants(float) throw (std::invalid_argument);
    float getMinDistants() const;

    void setGender(Human::Gender);
    Human::Gender getGender() const;

    void setRelation(Human::Relation);
    Human::Relation getRelation() const;

    void setRoughDistance(Human::RoughDistance);
    Human::RoughDistance getRoughDistance() const;

    SRMDeviation getFuzzyRule();
    void updaeFuzzyRules();

    void paint(QPaintDevice *) override;

    bool isGuidelineVisiable = true;
    bool ifDebug = false;

protected:
    int id_;
    float direction_;
    float directionOffset_;
    float velocity_;
    float minDistants_;
    float maxDistants_;
    Human::Gender gender_;
    Human::Relation relation_;
    Human::RoughDistance roughDistance_;
    Human::SocialRelationArea socialRelationArea_;
    SRMDeviation srmDeviation_;

    Human::SocialRelationArea getSocialRelationArea();
};

#endif // HUMAN_H
