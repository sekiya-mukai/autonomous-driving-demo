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
