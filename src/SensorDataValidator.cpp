#include "SensorDataValidator.hpp"

#include <cmath>

bool SensorDataValidator::isValid(
    const SensorData& sensorData) const
{
    // =====================================================
    // 非有限値チェック
    // =====================================================
    // NaN / +Infinity / -Infinity を拒否する。
    //
    // SDV-IV-004 ～ SDV-IV-009 に対応
    // =====================================================

    if (!std::isfinite(sensorData.egoSpeed))
    {
        return false;
    }

    if (!std::isfinite(sensorData.frontSpeed))
    {
        return false;
    }

    if (!std::isfinite(sensorData.distance))
    {
        return false;
    }

    // =====================================================
    // 負値チェック
    // =====================================================
    // SDV-IV-001 ～ SDV-IV-003 に対応
    // =====================================================

    if (sensorData.egoSpeed < 0.0)
    {
        return false;
    }

    if (sensorData.frontSpeed < 0.0)
    {
        return false;
    }

    if (sensorData.distance < 0.0)
    {
        return false;
    }

    return true;
}
