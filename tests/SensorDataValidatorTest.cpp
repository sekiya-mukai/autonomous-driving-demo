#include <gtest/gtest.h>

#include "SensorDataValidator.hpp"

// =====================================================
// Invalid Value Tests
// =====================================================
//
// Test specification:
//   SDV-IV-001 ～ SDV-IV-003
//
// Each GoogleTest case corresponds 1-to-1 with
// a test case ID in the test specification.
// =====================================================


// =====================================================
// SDV-IV-001
// =====================================================
//
// egoSpeed が負値の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_001_NegativeEgoSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        -0.1,  // egoSpeed [km/h] : INVALID
        50.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-002
// =====================================================
//
// frontSpeed が負値の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_002_NegativeFrontSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        -0.1,  // frontSpeed [km/h] : INVALID
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-003
// =====================================================
//
// distance が負値の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_003_NegativeDistance)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        -0.1   // distance [m] : INVALID
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}

// SDV-IV-001～003 : 負値
// SDV-IV-004～006 : NaN
// SDV-IV-007～009 : +∞
// SDV-IV-010～012 : -∞


// =====================================================
// SDV-IV-004
// =====================================================
//
// egoSpeed が NaN の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_004_NaNEgoSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        std::numeric_limits<double>::quiet_NaN(),
        50.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-005
// =====================================================
//
// frontSpeed が NaN の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_005_NaNFrontSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        std::numeric_limits<double>::quiet_NaN(),
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-006
// =====================================================
//
// distance が NaN の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_006_NaNDistance)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        std::numeric_limits<double>::quiet_NaN()
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-007
// =====================================================
//
// egoSpeed が +∞ の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_007_PositiveInfinityEgoSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        std::numeric_limits<double>::infinity(),
        50.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-008
// =====================================================
//
// frontSpeed が +∞ の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_008_PositiveInfinityFrontSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        std::numeric_limits<double>::infinity(),
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-009
// =====================================================
//
// distance が +∞ の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_009_PositiveInfinityDistance)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        std::numeric_limits<double>::infinity()
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-010
// =====================================================
//
// egoSpeed が -∞ の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_010_NegativeInfinityEgoSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        -std::numeric_limits<double>::infinity(),
        50.0,  // frontSpeed [km/h]
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-011
// =====================================================
//
// frontSpeed が -∞ の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_011_NegativeInfinityFrontSpeed)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        -std::numeric_limits<double>::infinity(),
        30.0   // distance [m]
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}


// =====================================================
// SDV-IV-012
// =====================================================
//
// distance が -∞ の場合
//
TEST(
    SensorDataValidatorInvalidValueTest,
    SDV_IV_012_NegativeInfinityDistance)
{
    SensorDataValidator validator;

    SensorData sensorData{
        50.0,  // egoSpeed [km/h]
        40.0,  // frontSpeed [km/h]
        -std::numeric_limits<double>::infinity()
    };

    const bool actual =
        validator.isValid(sensorData);

    EXPECT_FALSE(actual);
}
