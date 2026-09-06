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

// =====================================================
// Boundary Value Tests
// =====================================================
//
// Test specification:
//   CD-BV-001 ～ CD-BV-006
//
// Boundary 1:
//   relativeSpeed = egoSpeed - frontSpeed
//
// Boundary 2:
//   TTC = 3.0 seconds
//
// Each GoogleTest case corresponds 1-to-1 with
// a test case ID in the test specification.
// =====================================================


// =====================================================
// CD-BV-001
// =====================================================
//
// 相対速度が0未満。
// 前方車両の方が速いため、衝突リスクなし。
//
// Boundary:
//   relativeSpeed < 0
//
TEST(
    CollisionDetectorBoundaryTest,
    CD_BV_001_RelativeSpeedBelowZero)
{
    CollisionDetector detector;

    SensorData sensorData{
        59.9,  // egoSpeed [km/h]
        60.0,  // frontSpeed [km/h]
        20.0   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// CD-BV-002
// =====================================================
//
// 相対速度が0。
// 自車と前方車両が同速度のため、衝突リスクなし。
//
// Boundary:
//   relativeSpeed = 0
//
TEST(
    CollisionDetectorBoundaryTest,
    CD_BV_002_RelativeSpeedAtZero)
{
    CollisionDetector detector;

    SensorData sensorData{
        60.0,  // egoSpeed [km/h]
        60.0,  // frontSpeed [km/h]
        20.0   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// CD-BV-003
// =====================================================
//
// 相対速度が0よりわずかに大きい。
// TTC計算の分岐へ到達することを確認する。
// このケースではTTCが3秒を大きく超えるため、
// 衝突リスクなし。
//
// Boundary:
//   relativeSpeed > 0
//
TEST(
    CollisionDetectorBoundaryTest,
    CD_BV_003_RelativeSpeedAboveZero)
{
    CollisionDetector detector;

    SensorData sensorData{
        60.1,  // egoSpeed [km/h]
        60.0,  // frontSpeed [km/h]
        20.0   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// CD-BV-004
// =====================================================
//
// TTCが3秒未満。
// 衝突リスクあり。
//
// relativeSpeed:
//   50 - 40 = 10 km/h
//            = 2.777... m/s
//
// TTC:
//   8.30 / 2.777... ≈ 2.988 sec
//
// Boundary:
//   TTC < 3.0
//
TEST(
    CollisionDetectorBoundaryTest,
    CD_BV_004_TtcJustBelowThreshold)
{
    CollisionDetector detector;

    SensorData sensorData{
        36.0,  // egoSpeed [km/h]
        0.0,   // frontSpeed [km/h]
        29.9   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_TRUE(actual);

}


// =====================================================
// CD-BV-005
// =====================================================
//
// TTCが3秒ちょうど。
// 実装では「TTC < 3.0」の場合のみ危険と判定するため、
// TTC = 3.0では衝突リスクなし。
//
// relativeSpeed:
//   50 - 40 = 10 km/h
//            = 2.777... m/s
//
// distance:
//   2.777... × 3.0 ≈ 8.333333 m
//
// Boundary:
//   TTC = 3.0
//
TEST(
    CollisionDetectorBoundaryTest,
    CD_BV_005_TtcAtThreshold)
{
    CollisionDetector detector;

    SensorData sensorData{
        36.0,  // egoSpeed [km/h]
        0.0,   // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);

}


// =====================================================
// CD-BV-006
// =====================================================
//
// TTCが3秒を超える。
// 衝突リスクなし。
//
// relativeSpeed:
//   50 - 40 = 10 km/h
//            = 2.777... m/s
//
// TTC:
//   8.40 / 2.777... ≈ 3.024 sec
//
// Boundary:
//   TTC > 3.0
//
TEST(
    CollisionDetectorBoundaryTest,
    CD_BV_006_TtcJustAboveThreshold)
{
    CollisionDetector detector;

    SensorData sensorData{
        36.0,  // egoSpeed [km/h]
        0.0,   // frontSpeed [km/h]
        30.1   // distance [m]
    };

    const bool actual =
        detector.isCollisionRisk(sensorData);

    EXPECT_FALSE(actual);

}
