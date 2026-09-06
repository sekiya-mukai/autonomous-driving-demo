#include "PIDController.hpp"

PIDController::PIDController(
    double kp,
    double ki,
    double kd)
    : kp_(kp),
      ki_(ki),
      kd_(kd),
      integral_(0.0),
      previousError_(0.0)
{
}



double PIDController::calculate(
    double targetSpeed,
    double currentSpeed,
    double dt)
{
    // P = Kp × 現在の誤差
    const double error = targetSpeed - currentSpeed;
    
    // I = Ki × 誤差の積分
    integral_ += error * dt;
    
    // D = Kd × 誤差の変化速度
    const double derivative =
        (error - previousError_) / dt;

    const double output =
        kp_ * error
        + ki_ * integral_
        + kd_ * derivative;

    previousError_ = error;

    return output;
}
