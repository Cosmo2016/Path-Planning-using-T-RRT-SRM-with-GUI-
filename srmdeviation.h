#ifndef SRMPARAMETERS_H
#define SRMPARAMETERS_H


class SRMdeviation
{
public:
    SRMdeviation(float, float, float, float);

    void setSigma1(float);
    float getSigma1() const;

    void setSigma2(float);
    float getSigma2() const;

    void setVelocityDev(float);
    float getVelocityDev() const;

    void setProbabilityRatio(float);
    float getProbabilityRatio() const;

protected:
    float sigma1_;
    float sigma2_;
    float velocityDev_;
    float probabilityRatio_;
};

#endif // SRMPARAMETERS_H
