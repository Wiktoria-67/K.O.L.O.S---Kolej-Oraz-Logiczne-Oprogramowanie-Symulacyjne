#include <iostream>
#include "SmallTrain.h"

namespace Logistics {

    SmallTrain::SmallTrain() {
        maxCapacity = 2;       // Niska pojemność
        currentCapacity = 0;
        speed = 10.0f;         // Wysoka prędkość maksymalna
    }

    void SmallTrain::loadResource() {
        Train::loadResource();
        std::cout << "[SmallTrain] Ekspresowy zaladunek kurierski. Stan: "
                  << currentCapacity << "/" << maxCapacity << "\n";
    }

}
