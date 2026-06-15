#include <iostream>
#include "LargeTrain.h"

namespace Logistics {

    LargeTrain::LargeTrain() {
        maxCapacity = 12;     //Wysoka pojemność
        currentCapacity = 0;
        speed = 3.0f;          //Mała prędkość maksymalna
    }

    void LargeTrain::loadResource() {
        Train::loadResource();
        std::cout << "[LargeTrain] Uruchomiono ciezkie dzwigi. Masowy zaladunek kontenera. Stan: "
                  << currentCapacity << "/" << maxCapacity << "\n";
    }

}