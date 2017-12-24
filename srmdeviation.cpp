#include "srmdeviation.h"
#include <iostream>

SRMDeviation::SRMDeviation()
{
    this->sigma1_ = -1;
    this->sigma2_ = -1;
    this->velocityDev_ = -1;
    this->probabilityRatio_ = -1;
}
SRMDeviation::SRMDeviation(float sigma1, float sigma2, float velocityDev, float probabilityRatio)
{
    this->sigma1_ = sigma1;
    this->sigma2_ = sigma2;
    this->velocityDev_ = velocityDev;
    this->probabilityRatio_ = probabilityRatio;
}


void SRMDeviation::setSigma1(float sigma1)
{
    this->sigma1_ = sigma1;
}
float SRMDeviation::getSigma1() const
{
    return this->sigma1_;
}

void SRMDeviation::setSigma2(float sigma2)
{
    this->sigma2_ = sigma2;
}

float SRMDeviation::getSigma2() const
{
    return this->sigma2_;
}

void SRMDeviation::setVelocityDev(float velocityDev)
{
    this->velocityDev_ = velocityDev;
}

float SRMDeviation::getVelocityDev() const
{
    return this->velocityDev_;
}

void SRMDeviation::setProbabilityRatio(float probabilityRatio)
{
    std::cout << "Set probability ratio = " << probabilityRatio << std::endl;
    this->probabilityRatio_ = probabilityRatio;
}

float SRMDeviation::getProbabilityRatio() const
{
    return this->probabilityRatio_;
}

bool SRMDeviation::isEmpty()
{
    if (this->sigma1_ == -1 && this->sigma2_ == -1
            && this->velocityDev_ == -1
            && this->probabilityRatio_ == -1) {
        return true;
    } else {
        return false;
    }
}
