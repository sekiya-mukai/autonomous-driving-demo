#include <gtest/gtest.h>
#include "TTCCalculator.hpp"

TEST(
    TTCCalculatorTest,
    CalculateTTC)
{
    TTCCalculator calculator;
    EXPECT_DOUBLE_EQ(
        calculator.calculate
            20.0,
            10.0),
        2.0);
}

