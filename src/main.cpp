#include <iostream>

#include "AdaptiveCruiseControl.hpp"
#include "CollisionDetector.hpp"

int main()
{
    // センサから取得したと仮定する車両情報
    //
    // egoSpeed   : 自車速度 [km/h]
    // frontSpeed : 前方車両速度 [km/h]
    // distance   : 前方車両との距離 [m]
    SensorData sensorData
    {
        80.0,
        50.0,
        20.0
    };

    // ACCの目標速度を100km/hに設定
    AdaptiveCruiseControl acc(100.0);

    // 衝突リスク判定モジュール
    CollisionDetector detector;

    
    

    // センサ情報からACCの目標速度を計算
    //
    // 前方車両が近い場合は減速し、
    // 安全な距離が確保されている場合は設定速度を維持する
    const double targetSpeed =
        acc.calculateTargetSpeed(sensorData);

    // センサ情報から衝突リスクを判定
    //
    // TTC(Time To Collision)を利用して
    // 衝突の危険性があるかを評価する
    const bool collisionRisk =
        detector.isCollisionRisk(sensorData);

    // 計算された目標速度を表示
    std::cout << "Target Speed : "
              << targetSpeed
              << " km/h\n";

              // 衝突リスクの判定結果を表示
              std::cout << "Collision Risk : "
              << std::boolalpha
              << collisionRisk
              << '\n';

    // 追加(9/9)
    TTCCalculator ttcCalculator;

    EmergencyBrakeSystem aeb;

    double ttc =
        ttcCalculator.calculate(
            disntance,
            relativeSpeed);
    
    BrakeLevel brakeLevel =
        aeb.evaluate(ttc);
    
    std::cout
    << "TTC: "
    << ttc
    << std::endl;
              

    return 0;
}