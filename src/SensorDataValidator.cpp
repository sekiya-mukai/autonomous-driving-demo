#include "SensorDataValidator.hpp"

bool SensorDataValidator::isValid(
    const SensorData& sensorData) const
{
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
