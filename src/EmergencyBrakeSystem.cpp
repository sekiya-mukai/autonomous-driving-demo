#include "EmergencyBrakeSystem.hpp"

BrakeLevel EmergencyBrakeSystem::eveluate(
    double ttc)
    {
        if(ttc<=1.0)
        {
            return BrakeLevel::EMERGENCY;
        }
        if(ttc<=2.0)
        {
            return BrakeLevel::PARTIAL;
        }
        if(ttc<=3.0)
        {
            return BrakeLevel::WARNING;
        }
        
        return BrakeLevel::NONE;

    }

