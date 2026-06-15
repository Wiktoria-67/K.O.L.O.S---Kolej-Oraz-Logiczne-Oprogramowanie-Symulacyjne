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

        /**
         * @brief Zwraca całkowitą dostępną energię w systemie.
         * @return Liczba jednostek wygenerowanego prądu.
         */
        int getGeneratedEnergy() const { return generatedEnergy; }

        /**
         * @brief Pobiera (zużywa) określoną ilość prądu z sieci na potrzeby innych budynków.
         * @param amount Ilość prądu do skonsumowania.
         */
        void consumeEnergy(int amount) { if (generatedEnergy >= amount) generatedEnergy -= amount; }
    };

}