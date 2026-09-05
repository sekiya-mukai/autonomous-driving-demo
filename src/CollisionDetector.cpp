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
    const double relativeSpeed =
        sensorData.egoSpeed -
        sensorData.frontSpeed;

    // 前方車両の方が速い場合は安全
    if (relativeSpeed <= 0.0)
    {
        return false;
    }

    // TTC計算
    const double ttc =
        sensorData.distance / relativeSpeed;

    // TTCが閾値未満なら危険
    return ttc < TTC_THRESHOLD_S;
}