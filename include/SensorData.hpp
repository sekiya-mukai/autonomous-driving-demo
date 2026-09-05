/**
 * @file SensorData.hpp
 * @brief Sensor data model used by autonomous driving modules
 * @author S. Mukai
 */


#pragma once

/**
 * @brief 車両センサ情報
 *
 * 自車と前方車両の状態を保持する。
 *
 * 実際の自動運転システムでは、
 * カメラ、LiDAR、レーダ等から取得した
 * センサ情報を統合して生成されることを想定する。
 */
struct SensorData
{
    /// 自車速度[km/h]
    double egoSpeed;

    /// 前方車両速度[km/h]
    double frontSpeed;

    /// 前方車両との距離[m]
    double distance;
};