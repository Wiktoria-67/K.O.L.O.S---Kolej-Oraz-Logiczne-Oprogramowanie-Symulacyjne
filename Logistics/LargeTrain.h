#pragma once
#include "Train.h"

namespace Logistics {

    /**
     * @class LargeTrain
     * @brief Reprezentuje duży, wolny pociąg towarowy o ogromnej ładowności.
     */
    class LargeTrain : public Train {
    public:
        /**
         * @brief Inicjalizuje duży pociąg (maxCapacity = 12, speed = 3.0f).
         */
        LargeTrain();

        /**
         * @brief Polimorficzne ładowanie surowca dla ciężkiego składu towarowego.
         * * Wywołuje procedurę masowego załadunku kontenerowego przy użyciu ciężkich dźwigów stacyjnych.
         * @throw CapacityExceededException Jeśli próba przeładunku przekroczy maksymalną ładowność składu.
         */
        void loadResource() override;
    };

}