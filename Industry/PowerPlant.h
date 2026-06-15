#pragma once
#include "Factory.h"

namespace Industry {

    /**
     * @class PowerPlant
     * @brief Reprezentuje elektrownię węglową generującą energię dla systemu.
     */
    class PowerPlant : public Factory {
        private:
    int generatedEnergy = 0; // NOWE
    public:
        /**
         * @brief Inicjalizuje parametry elektrowni (korzysta tylko z inputBufferA na węgiel).
         */
        PowerPlant();

        /**
         * @brief Konsumuje jedną jednostkę węgla i generuje moc.
         * @throw EmptyStorageException Jeśli zabraknie węgla.
         */
        void processResources() override;
        int getGeneratedEnergy() const { return generatedEnergy; } // NOWE
    };

}