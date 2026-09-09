#include <gtest/gtest.h>
#include "EmergencyBrakeSystem.hpp"

TEST(
    EmergencyBrakeSystemTest,
    EmergencyBrake)
{
    EmergencyBrakeSystem aeb;
    EXPECT_EQ(
        arb.evaluate(0.8),
        BrakeLevel::EMERGENCY);
}

