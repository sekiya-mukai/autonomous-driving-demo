#pragma once

#include "CollisionDetector.hpp"
#include "SensorDataValidator.hpp"

class DrivingSafetyChecker
{
public:

    bool isCollisionRisk(
        const SensorData& sensorData) const;

private:

    SensorDataValidator validator_;
    CollisionDetector detector_;
};
