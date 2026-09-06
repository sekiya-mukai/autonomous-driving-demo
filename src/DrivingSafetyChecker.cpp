// isCollisionRisk()
//        │
//        ▼
// validator_.isValid()
//        │
//     ┌──┴──┐
//     NG    OK
//      │     │
//      ▼     ▼
//    false detector
//            │
//            ▼
//         result


#include "DrivingSafetyChecker.hpp"

bool DrivingSafetyChecker::isCollisionRisk(
    const SensorData& sensorData) const
{
    if (!validator_.isValid(sensorData))
    {
        return false;
    }

    return detector_.isCollisionRisk(sensorData);
}
