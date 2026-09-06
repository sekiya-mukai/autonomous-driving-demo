#pragma once

/**
 * @brief PID controller for vehicle speed control.
 *
 * 目標速度と現在速度の誤差から、
 * 車両への加速度指令を計算する。
 */
class PIDController
{
public:

    /**
     * @brief コンストラクタ
     *
     * @param kp 比例ゲイン
     * @param ki 積分ゲイン
     * @param kd 微分ゲイン
     */
    PIDController(
        double kp,
        double ki,
        double kd);

    /**
     * @brief 制御量を計算する
     *
     * @param targetSpeed 目標速度[km/h]
     * @param currentSpeed 現在速度[km/h]
     * @param dt 前回計算からの経過時間[s]
     * @return 加速度指令
     */
    double calculate(
        double targetSpeed,
        double currentSpeed,
        double dt);

private:

    double kp_;
    double ki_;
    double kd_;

    double integral_;
    double previousError_;
};
