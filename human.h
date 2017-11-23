#ifndef HUMAN_H
#define HUMAN_H

#include <shape.h>


class Human : public Shape
{
public:
    enum Operation {
        translation,
        rotation
    };

    /* enum Status {
        move,
    } */

    Human();
    ~Human();

    void setDirection(double);
    double getDirection() const;

    int getHumanId() const;

    void paint(QPaintDevice *) override;

protected:
    int id = -1;
    double direction_ = -1.0;
    double velocity_ = -1.0;

    int generateHumanId() const;
};

#endif // HUMAN_H
