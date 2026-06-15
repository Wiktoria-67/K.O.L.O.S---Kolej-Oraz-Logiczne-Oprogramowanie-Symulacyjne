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


        /**
         * @brief Polimorficzne ładowanie surowca dla pociągu średniego.
         * * Realizuje standardowy załadunek paletowy i rejestruje bieżący stan magazynu w logach.
         * @throw CapacityExceededException Jeśli ładownia pociągu osiągnęła maksymalny limit.
         */
        void loadResource() override;
    };

}