#include "AdaptiveCruiseControl.hpp"

AdaptiveCruiseControl::AdaptiveCruiseControl(
    double targetSpeed)
    : targetSpeed_(targetSpeed)
{
}

double AdaptiveCruiseControl::calculateTargetSpeed(
    const SensorData& sensorData) const
{
    constexpr double safeDistance = 30.0;

    if(sensorData.distance < safeDistance)
    {
        return sensorData.frontSpeed;
    }

    return targetSpeed_;
}