#pragma once
#include "Train.h"

namespace Logistics {

    /**
     * @class MediumTrain
     * @brief Reprezentuje średni pociąg będący kompromisem między prędkością a ładownością.
     */
    class MediumTrain : public Train {
    public:
        /**
         * @brief Inicjalizuje średni pociąg (maxCapacity = 5, speed = 6.0f).
         */
        MediumTrain();
    };

}