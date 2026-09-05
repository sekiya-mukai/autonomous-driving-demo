// Adaptive Cruise ControlとCollision Detectionの簡易シミュレータを
// C++17で実装しました。CMakeでビルド可能な構成にし、GoogleTestによる
// 単体テストも追加しました。
// 衝突判定ロジックはTTC(Time To Collision)を用いており、
// 正常系・非衝突系のテストケースを作成しています。


#include <gtest/gtest.h>

#include "CollisionDetector.hpp"

TEST(CollisionDetectorTest, DetectCollisionRisk)
{
    CollisionDetector detector;

    SensorData data
    {
        100.0, // egoSpeed
        50.0,  // frontSpeed
        20.0   // distance
    };

    EXPECT_TRUE(
        detector.isCollisionRisk(data)
    );
}

TEST(CollisionDetectorTest, NoCollisionRisk)
{
    CollisionDetector detector;

    SensorData data
    {
        80.0,
        80.0,
        50.0
    };

    EXPECT_FALSE(
        detector.isCollisionRisk(data)
    );
}

TEST(CollisionDetectorTest, FrontVehicleFaster)
{
    CollisionDetector detector;

    SensorData data
    {
        60.0,
        80.0,
        20.0
    };

    EXPECT_FALSE(
        detector.isCollisionRisk(data)
    );
}