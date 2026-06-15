#pragma once
#include "Factory.h"

namespace Industry {

    /**
     * @class MachineFactory
     * @brief Reprezentuje zaawansowaną fabrykę produkującą finalne dobra w łańcuchu.
     */
    class MachineFactory : public Factory {
        private:
    int victoryPoints = 0; 
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
        int getVictoryPoints() const { return victoryPoints; } // NOWE
    };

}