#pragma once
#include "Train.h"

namespace Logistics {

    /**
     * @class SmallTrain
     * @brief Reprezentuje mały pociąg o dużej prędkości, ale niewielkiej ładowności.
     */
    class SmallTrain : public Train { 
    public:
        /**
         * @brief Inicjalizuje mały pociąg (maxCapacity = 2, speed = 10.0f).
         */
        SmallTrain();
    };

}