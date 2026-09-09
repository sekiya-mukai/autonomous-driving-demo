#include "TTCCalculator.hpp"

double TTCCalculator::calculate(
    double disntace,
    double relativeSpeed)
    {
        if (relativeSpeed <= 0.0){
            return 9999.0;
        }
        
        return distance / relativeSpeed;
    }

