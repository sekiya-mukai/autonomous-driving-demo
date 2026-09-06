#include <gtest/gtest.h>

#include "CollisionDetector.hpp"

// =====================================================
// Functional Tests
// =====================================================
//
// Test specification:
//   CD-F-001 ～ CD-F-003
//
// Each GoogleTest case corresponds 1-to-1 with
// a test case ID in the test specification.
// =====================================================


// =====================================================
// CD-F-001
// =====================================================
//
// 自車速度 > 前方車両速度
// 車間距離も短いため、衝突リスクあり。
//
TEST(
    CollisionDetectorFunctionalTest,
    CD_F_001_DetectCollisionRisk)
{
    CollisionDetector detector;

    SensorData sensorData{
        100.0,  // egoSpeed [km/h]
        50.0,   // frontSpeed [km/h]
        20.0    // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_TRUE(actual);
}


// =====================================================
// CD-F-002
// =====================================================
//
// 自車速度 == 前方車両速度
// 相対速度がないため、衝突リスクなし。
//
TEST(
    CollisionDetectorFunctionalTest,
    CD_F_002_NoCollisionRisk)
{
    CollisionDetector detector;

    SensorData sensorData{
        80.0,  // egoSpeed [km/h]
        80.0,  // frontSpeed [km/h]
        50.0   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// CD-F-003
// =====================================================
//
// 前方車両速度 > 自車速度
// 相対的に距離が縮まらないため、衝突リスクなし。
//
TEST(
    CollisionDetectorFunctionalTest,
    CD_F_003_FrontVehicleFaster)
{
    CollisionDetector detector;

    SensorData sensorData{
        60.0,  // egoSpeed [km/h]
        80.0,  // frontSpeed [km/h]
        20.0   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}