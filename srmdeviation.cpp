#include "srmdeviation.h"

SRMdeviation::SRMdeviation(float sigma1, float sigma2, float velocityDev, float probabilityRatio)
{
    this->sigma1_ = sigma1;
    this->sigma2_ = sigma2;
    this->velocityDev_ = velocityDev;
    this->probabilityRatio_ = probabilityRatio;
}


void SRMdeviation::setSigma1(float sigma1)
{
    this->sigma1_ = sigma1;
}
float SRMdeviation::getSigma1() const
{
    return this->sigma1_;
}

void SRMdeviation::setSigma2(float sigma2)
{
    this->sigma2_ = sigma2;
}

float SRMdeviation::getSigma2() const
{
    return this->sigma2_;
}

void SRMdeviation::setVelocityDev(float velocityDev)
{
    this->velocityDev_ = velocityDev;
}

float SRMdeviation::getVelocityDev() const
{
    return this->velocityDev_;
}

void SRMdeviation::setProbabilityRatio(float probabilityRatio_)
{
    this->probabilityRatio_ = probabilityRatio_;
}

float SRMdeviation::getProbabilityRatio() const
{
    return this->probabilityRatio_;
}
