#pragma once

#include "BrakeCommand.hpp"

class EmergencyBrakeSystem
{
public:
    BrakeLevel evaluate(
        double ttc);    
};

