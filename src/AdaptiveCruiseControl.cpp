#include "AdaptiveCruiseControl.hpp"

namespace
{
    // 安全車間距離[m]
    constexpr double SAFE_DISTANCE_M = 30.0;
}

// コンストラクタ
AdaptiveCruiseControl::AdaptiveCruiseControl(
    double targetSpeed)
    : targetSpeed_(targetSpeed)
{
}

// Adaptive Cruise Control (ACC)
//
// 前方車両との距離に応じて目標速度を決定する。
double AdaptiveCruiseControl::calculateTargetSpeed(
    const SensorData& sensorData) const
{
    // 車間距離が不足している場合は前方車両に追従
    if (sensorData.distance < SAFE_DISTANCE_M)
    {
        return sensorData.frontSpeed;
    }

    // 巡航速度を維持
    return targetSpeed_;
}