#include <iostream>
#include "MediumTrain.h"

namespace Logistics {

    MediumTrain::MediumTrain() {
        maxCapacity = 5;       
        currentCapacity = 0;
        speed = 6.0f;          
    }

    void MediumTrain::loadResource() {
        Train::loadResource();
        std::cout << "[MediumTrain] Zaladowano standardowa palete towarowa. Stan: "
                  << currentCapacity << "/" << maxCapacity << "\n";
    }

}