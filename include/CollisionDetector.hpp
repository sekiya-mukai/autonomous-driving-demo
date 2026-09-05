/**
 * @file CollisionDetector.hpp
 * @brief Collision risk estimation module
 * @author S. Mukai
 */


#pragma once

#include "SensorData.hpp"

/**
 * @brief 衝突リスク判定クラス
 *
 * 前方車両との距離および速度差から
 * TTC(Time To Collision)を算出し、
 * 衝突リスクの有無を判定する。
 */
class CollisionDetector
{
public:

    /**
     * @brief 衝突リスク判定
     *
     * TTC(Time To Collision)を利用し、
     * 衝突の危険性を評価する。
     *
     * @param sensorData センサ入力情報
     * @return true  衝突リスクあり
     * @return false 衝突リスクなし
     */
    bool isCollisionRisk(
        const SensorData& sensorData) const;
};