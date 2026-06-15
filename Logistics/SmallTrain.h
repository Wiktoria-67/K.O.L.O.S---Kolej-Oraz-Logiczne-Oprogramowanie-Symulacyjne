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

        /**
         * @brief Polimorficzne ładowanie surowca specyficzne dla szybkiego pociągu.
         * * Wywołuje bazową logikę sprawdzania limitów pojemności, a następnie
         * generuje komunikat o ekspresowym załadunku kurierskim.
         * @throw CapacityExceededException Jeśli ładownia pociągu jest już całkowicie zapełniona.
         */
        void loadResource() override;
    };

}