/**
 * @file SensorDataValidator.hpp
 * @brief Sensor data validation module
 * @author S. Mukai
 */

#pragma once

#include "SensorData.hpp"

/**
 * @brief センサ入力値の妥当性を検証するクラス
 *
 * SensorDataに含まれる各パラメータが
 * 正常範囲にあるかを判定する。
 */
class SensorDataValidator
{
public:

    /**
     * @brief センサデータ全体の妥当性判定
     *
     * @param sensorData センサ入力情報
     * @return true  正常
     * @return false 異常
     */
    bool isValid(
        const SensorData& sensorData) const;
};
