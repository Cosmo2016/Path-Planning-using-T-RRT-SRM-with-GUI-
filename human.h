#ifndef HUMAN_H
#define HUMAN_H

#include <shape.h>


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

    Human();
    ~Human();

    void setDirection(float);
    double getDirection() const;

    int getHumanId() const;

    void paint(QPaintDevice *) override;

    bool isGuidelineVisiable = true;

    float maxDistants_ = 80.0;
    float minDistants_ = 25.0;

    bool ifDebug = false;

protected:
    int id;
    float direction_;
    float velocity_;
};

#endif // HUMAN_H
