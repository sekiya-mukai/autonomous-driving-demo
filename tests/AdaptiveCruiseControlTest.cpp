#include <gtest/gtest.h>

#include "AdaptiveCruiseControl.hpp"

// =====================================================
// Boundary Value Tests
// =====================================================
//
// Test specification:
//   ACC-BV-001 ～ ACC-BV-009
//
// Each GoogleTest case corresponds 1-to-1 with
// a test case ID in the test specification.
// =====================================================


// =====================================================
// targetSpeed
// =====================================================

// ACC-BV-001
// targetSpeed = 0.0 km/h
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_001_TargetSpeedAtZero)
{
    AdaptiveCruiseControl acc(0.0);

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 0.0);
}


// ACC-BV-002
// targetSpeed = 0.1 km/h
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_002_TargetSpeedJustAboveZero)
{
    AdaptiveCruiseControl acc(0.1);

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 0.1);
}


// =====================================================
// egoSpeed
// =====================================================

// ACC-BV-003
// egoSpeed = 0.0 km/h
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_003_EgoSpeedAtZero)
{
    AdaptiveCruiseControl acc(50.0);

    SensorData sensorData{
        0.0,   // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 50.0);
}


// ACC-BV-004
// egoSpeed = 0.1 km/h
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_004_EgoSpeedJustAboveZero)
{
    AdaptiveCruiseControl acc(50.0);

    SensorData sensorData{
        0.1,   // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 50.0);
}


// =====================================================
// frontSpeed
// =====================================================

// ACC-BV-005
// frontSpeed = 0.0 km/h
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_005_FrontSpeedAtZero)
{
    AdaptiveCruiseControl acc(50.0);

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        0.0,   // frontSpeed [km/h]
        29.9   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 0.0);
}


// ACC-BV-006
// frontSpeed = 0.1 km/h
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_006_FrontSpeedJustAboveZero)
{
    AdaptiveCruiseControl acc(50.0);

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        0.1,   // frontSpeed [km/h]
        29.9   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 0.1);
}


// =====================================================
// distance
// =====================================================

// ACC-BV-007
// distance = 29.9 m
// Just below SAFE_DISTANCE_M = 30.0 m
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_007_DistanceJustBelowSafeDistance)
{
    AdaptiveCruiseControl acc(50.0);

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        29.9   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 40.0);
}


// ACC-BV-008
// distance = 30.0 m
// Exactly at SAFE_DISTANCE_M
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_008_DistanceAtSafeDistance)
{
    AdaptiveCruiseControl acc(50.0);

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 50.0);
}


// ACC-BV-009
// distance = 30.1 m
// Just above SAFE_DISTANCE_M = 30.0 m
TEST(
    AdaptiveCruiseControlBoundaryTest,
    ACC_BV_009_DistanceJustAboveSafeDistance)
{
    AdaptiveCruiseControl acc(50.0);

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        30.1   // distance [m]
    };

    const double actual =
        acc.calculateTargetSpeed(sensorData);

    EXPECT_DOUBLE_EQ(actual, 50.0);
}
