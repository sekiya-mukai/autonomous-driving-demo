#include <gtest/gtest.h>

#include "DrivingSafetyChecker.hpp"

// =====================================================
// Integration Tests
// =====================================================
//
// Test specification:
//   SDV-IT-001 ～ SDV-IT-004
//
// SensorData
//     ↓
// SensorDataValidator
//     ↓
//     NG → CollisionDetectorには渡さない
//     ↓
//     OK → CollisionDetectorへ渡す
// =====================================================


// =====================================================
// SDV-IT-001
// =====================================================
//
// 負の自車速度
// ValidatorがNGと判定するため、
// CollisionDetectorによる衝突判定を行わない。
//
TEST(
    SensorDataIntegrationTest,
    SDV_IT_001_NegativeEgoSpeedRejected)
{
    DrivingSafetyChecker checker;

    SensorData sensorData{
        -1.0,   // egoSpeed [km/h]
        50.0,   // frontSpeed [km/h]
        20.0    // distance [m]
    };

    const bool actual =
        checker.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IT-002
// =====================================================
//
// 負の前方車両速度
// ValidatorがNGと判定するため、
// CollisionDetectorによる衝突判定を行わない。
//
TEST(
    SensorDataIntegrationTest,
    SDV_IT_002_NegativeFrontSpeedRejected)
{
    DrivingSafetyChecker checker;

    SensorData sensorData{
        100.0,
        -1.0,
        20.0
    };

    const bool actual =
        checker.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IT-003
// =====================================================
//
// 負の車間距離
// ValidatorがNGと判定するため、
// CollisionDetectorによる衝突判定を行わない。
//
TEST(
    SensorDataIntegrationTest,
    SDV_IT_003_NegativeDistanceRejected)
{
    DrivingSafetyChecker checker;

    SensorData sensorData{
        100.0,
        50.0,
        -1.0
    };

    const bool actual =
        checker.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IT-004
// =====================================================
//
// 正常なSensorData
// ValidatorがOKと判定し、
// CollisionDetectorによる衝突判定を行う。
//
TEST(
    SensorDataIntegrationTest,
    SDV_IT_004_ValidSensorDataAccepted)
{
    DrivingSafetyChecker checker;

    SensorData sensorData{
        100.0,
        50.0,
        20.0
    };

    const bool actual =
        checker.isCollisionRisk(sensorData);

    EXPECT_TRUE(actual);
}
