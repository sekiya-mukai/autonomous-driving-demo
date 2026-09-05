#pragma once

#include "SensorData.hpp"

class CollisionDetector
{
public:
    bool isCollisionRisk(
        const SensorData& sensorData) const;
};