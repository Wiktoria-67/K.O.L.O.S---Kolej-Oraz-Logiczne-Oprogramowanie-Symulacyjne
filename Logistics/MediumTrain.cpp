#include "MediumTrain.h"

namespace Logistics {

    MediumTrain::MediumTrain() {
        // Zbalansowane parametry ruchu i optymalna ładownia
        maxCapacity = 5;       
        currentCapacity = 0;
        speed = 6.0f;          
    }

} // namespace Logistics