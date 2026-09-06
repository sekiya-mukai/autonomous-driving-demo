/**
 * @file AdaptiveCruiseControl.hpp
 * @brief Adaptive Cruise Control module
 * @author S. Mukai
 */


#pragma once

#include "SensorData.hpp"

/**
 * @brief Adaptive Cruise Control (ACC)
 *
 * 前方車両との距離に応じて目標速度を決定するクラス。
 *
 * 車間距離が十分に確保されている場合は
 * ドライバーが設定した巡航速度を維持する。
 *
 * 車間距離が不足している場合は
 * 前方車両に追従するように減速する。
 */
class AdaptiveCruiseControl
{
public:

    /**
     * @brief コンストラクタ
     *
     * @param targetSpeed 巡航目標速度[km/h]
     */
    //  explicit 意図しない暗黙変換を防ぐため
    explicit AdaptiveCruiseControl(double targetSpeed);

    /**
     * @brief ACCによる目標速度計算
     *
     * @param sensorData センサ入力情報
     * @return 計算後の目標速度[km/h]
     */
    double calculateTargetSpeed(
        const SensorData& sensorData) const;

private:

    /// ドライバーが設定した巡航速度[km/h]
    double targetSpeed_;
};