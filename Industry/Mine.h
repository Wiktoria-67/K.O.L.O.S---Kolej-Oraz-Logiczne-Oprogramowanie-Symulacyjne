#pragma once
#include "../Core/MapObject.h"

namespace Industry {

    /**
     * @class Mine
     * @brief Abstrakcyjna klasa bazowa dla budynków wydobywczych (kopalni).
     * * Obiekty dziedziczące po tej klasie generują surowce w oparciu o pętle czasowe.
     */
    class Mine : public Core::MapObject {
    protected:
        int resourceTimer; ///< Licznik czasu (w tickach symulacji) do wygenerowania surowca.
    private:
        int outputBuffer = 0; ///< Prywatny magazyn wyjściowy kopalni na wykopane surowce.
    public:
        virtual ~Mine() = default;
        
        /**
         * @brief Renderuje obiekt kopalni w przestrzeni symulacyjnej.
         * @param window Referencja do okna SFML.
         */
        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Aktualizuje licznik czasu. Po zejściu do zera wywołuje generateResource().
         */
        void update() override;
        
        /**
         * @brief Definiuje sposób i rodzaj dodawanego surowca do bufora wyjściowego kopalni.
         */
        virtual void generateResource() = 0;

        /**
         * @brief Pobiera aktualną liczbę jednostek surowca czekających w magazynie wyjściowym.
         * @return Liczba jednostek surowca gotowych do załadunku.
         */
        int getOutputBuffer() const { return outputBuffer; }

        /**
         * @brief Zwiększa stan magazynu wyjściowego o określoną liczbę jednostek.
         * * Posiada wbudowaną walidację – wartości ujemne oraz zerowe są ignorowane.
         * @param amount Liczba jednostek surowca do dodania do magazynu.
         */
        void increaseOutputBuffer(int amount) { if(amount > 0) outputBuffer += amount; }

        /**
         * @brief Zmniejsza stan magazynu wyjściowego o określoną liczbę jednostek.
         * * Posiada wbudowane zabezpieczenie przed błędami logicznymi (nie pozwoli zejść poniżej zera).
         * @param amount Liczba jednostek surowca pobierana przez pociąg.
         */
        void decreaseOutputBuffer(int amount) { if(outputBuffer >= amount) outputBuffer -= amount; }
    };

}