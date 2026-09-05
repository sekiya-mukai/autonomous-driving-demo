#include <iostream>

#include "AdaptiveCruiseControl.hpp"
#include "CollisionDetector.hpp"

int main()
{
    SensorData sensorData
    {
        80.0,
        50.0,
        20.0
    };

    AdaptiveCruiseControl acc(100.0);
    CollisionDetector detector;

    const double targetSpeed =
        acc.calculateTargetSpeed(sensorData);

    const bool collisionRisk =
        detector.isCollisionRisk(sensorData);

    std::cout << "Target Speed : "
              << targetSpeed
              << " km/h\n";

    std::cout << "Collision Risk : "
              << std::boolalpha
              << collisionRisk
              << '\n';

    return 0;
}