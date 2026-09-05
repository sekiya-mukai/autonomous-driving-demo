#pragma once

#include "SensorData.hpp"

class AdaptiveCruiseControl
{
public:
    explicit AdaptiveCruiseControl(double targetSpeed);

    double calculateTargetSpeed(
        const SensorData& sensorData) const;

private:
    double targetSpeed_;
};