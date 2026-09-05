#include "CollisionDetector.hpp"

bool CollisionDetector::isCollisionRisk(
    const SensorData& sensorData) const
{
    const double relativeSpeed =
        sensorData.egoSpeed -
        sensorData.frontSpeed;

    if(relativeSpeed <= 0.0)
    {
        return false;
    }

    const double ttc =
        sensorData.distance / relativeSpeed;

    return ttc < 3.0;
}