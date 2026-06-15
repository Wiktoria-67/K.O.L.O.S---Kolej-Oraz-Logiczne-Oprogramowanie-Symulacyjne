#pragma once
#include "../Core/MapObject.h"

/**
 * @namespace Industry
 * @brief Moduł odpowiedzialny za produkcję, wydobycie i przetwarzanie surowców.
 */
namespace Industry {

    /**
     * @class Factory
     * @brief Abstrakcyjna klasa bazowa dla wszystkich fabryk w symulacji.
     * * Dziedziczy po Core::MapObject. Zarządza buforami wejściowymi surowców
     * i definiuje wspólną architekturę procesu produkcyjnego.
     */
    class Factory : public Core::MapObject {
    protected:
        int inputBufferA; ///< Bufor przechowujący główny surowiec wejściowy.
        int inputBufferB; ///< Bufor pomocniczy na ewentualny drugi surowiec (np. dla hut).
    public:
        virtual ~Factory() = default;

        /**
         * @brief Renderuje obiekt fabryki w przestrzeni symulacyjnej.
         * @param window Referencja do okna SFML.
         */
        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Główna pętla fabryki.
         * * Posiada wbudowaną obsługę wyjątków (try-catch dla EmptyStorageException),
         * dzięki czemu bezpiecznie pauzuje produkcję w wypadku przerw w dostawach.
         */
        void update() override;

        /**
         * @brief Przetwarza surowce z buforów wejściowych na wynikową produkcję.
         * @throw EmptyStorageException Zgłaszany automatycznie, gdy w buforze brakuje materiału.
         */
        virtual void processResources() = 0; 
    };

}