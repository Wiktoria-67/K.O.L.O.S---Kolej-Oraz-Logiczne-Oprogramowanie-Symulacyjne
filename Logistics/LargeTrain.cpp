#include "LargeTrain.h"

namespace Logistics {

    LargeTrain::LargeTrain() {
        // Niska prędkość, potężna pojemność ładowni
        maxCapacity = 12;      
        currentCapacity = 0;
        speed = 3.0f;          
    }

} // namespace Logistics