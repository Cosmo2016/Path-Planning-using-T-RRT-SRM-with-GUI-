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
    float getMaxDistants() const;
    float getMinDistants() const;

    void paint(QPaintDevice *) override;

    bool isGuidelineVisiable = true;
    bool ifDebug = false;

private:
    int id;
    float direction_;
    float velocity_;
    float minDistants_;
    float maxDistants_;
};

#endif // HUMAN_H
