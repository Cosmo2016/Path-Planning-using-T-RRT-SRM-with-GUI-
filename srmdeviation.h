#ifndef SRMDEVIATION_H
#define SRMDEVIATION_H

class SRMDeviation
{
public:
    SRMDeviation();
    SRMDeviation(float, float, float, float);

    void setSigma1(float);
    float getSigma1() const;

    void setSigma2(float);
    float getSigma2() const;

    void setVelocityDev(float);
    float getVelocityDev() const;

    void setProbabilityRatio(float);
    float getProbabilityRatio() const;

    bool isEmpty();

protected:
    float sigma1_;
    float sigma2_;
    float velocityDev_;
    float probabilityRatio_;
};

#endif // SRMDEVIATION_H
