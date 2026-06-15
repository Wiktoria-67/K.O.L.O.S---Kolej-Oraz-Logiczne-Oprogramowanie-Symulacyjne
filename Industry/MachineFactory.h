#pragma once
#include "Factory.h"
#include "PowerPlant.h"

namespace Industry {

    /**
     * @class MachineFactory
     * @brief Reprezentuje zaawansowaną fabrykę produkującą finalne dobra w łańcuchu.
     */
    class MachineFactory : public Factory {
        private:
            int victoryPoints = 0; ///< Aktualny licznik wygenerowanych punktów zwycięstwa.
            PowerPlant* powerGrid = nullptr; ///< Wskaźnik na podłączoną elektrownię dostarczającą prąd.
    public:
        /**
         * @brief Inicjalizuje fabrykę (korzysta z inputBufferA przyjmującego stal).
         */
        MachineFactory();


        /**
         * @brief Konsumuje stal generując punkty zwycięstwa lub komponenty końcowe.
         * @throw EmptyStorageException Jeśli w magazynie brakuje dostaw z huty.
         */
        void processResources() override;

        /**
         * @brief Zwraca łączną liczbę punktów zwycięstwa wygenerowanych przez fabrykę.
         * @return Liczba punktów zwycięstwa.
         */
        int getVictoryPoints() const { return victoryPoints; }

        /**
         * @brief Łączy fabrykę z zewnętrzną siecią energetyczną.
         * @param pp Wskaźnik na obiekt elektrowni (PowerPlant).
         */
        void connectToGrid(PowerPlant* pp) { powerGrid = pp; }
    };

}