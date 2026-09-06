#include "CollisionDetector.hpp"

namespace
{
    // TTC(Time To Collision)の閾値[秒]
    constexpr double TTC_THRESHOLD_S = 3.0;
}

// 衝突リスク判定
bool CollisionDetector::isCollisionRisk(
    const SensorData& sensorData) const
{
    // 相対速度
    const double relativeSpeedKmh =
        sensorData.egoSpeed -
        sensorData.frontSpeed;

// relativeSpeed < 0 : CD-BV-001  -0.1
// relativeSpeed = 0 : CD-BV-002   0.0
// relativeSpeed > 0 : CD-BV-003  +0.1


    if (relativeSpeedKmh <= 0.0)
    {
        return false;
    }

    const double relativeSpeedMs =
        relativeSpeedKmh / 3.6;

    const double ttc =
        sensorData.distance / relativeSpeedMs;

    return ttc < TTC_THRESHOLD_S;

}