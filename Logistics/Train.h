#pragma once
#include "../Core/MapObject.h"
#include "Route.h"

namespace Logistics {

    /**
     * @class Train
     * @brief Abstrakcyjna klasa bazowa dla wszystkich pociągów w symulacji.
     * * Dziedziczy po Core::MapObject. Hermetyzuje parametry ładowności,
     * prędkości oraz logikę poruszania się po wyznaczonej trasie.
     */
    class Train : public Core::MapObject {
    protected:
        int currentCapacity; ///< Aktualna liczba surowców w ładowni.
        int maxCapacity; ///< Maksymalna pojemność ładowni pociągu.
        float speed; ///< Prędkość poruszania się pociągu (jednostki na tick).
        
        Route route; ///< Trasa przypisana do pociągu.
        size_t currentWaypointIndex = 0; ///< Indeks aktualnego celu na trasie.

    public:
        virtual ~Train() = default;

        /**
         * @brief Renderuje pociąg w oknie symulacji.
         * @param window Referencja do okna SFML, na którym rysowany jest obiekt.
         */
        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Aktualizuje pozycję pociągu na podstawie jego prędkości i trasy.
         * * Wywoływana w każdej klatce symulacji przez silnik (SimulationEngine).
         */
        void update() override;

        /**
         * @brief Ładuje jedną jednostkę surowca do pociągu.
         * @throw CapacityExceededException Jeśli ładownia jest już pełna.
         */
        virtual void loadResource();
        
        /**
         * @brief Przypisuje nową trasę przejazdu i resetuje pozycję na stację początkową.
         * @param newRoute Nowa trasa do pokonania.
         */
        void setRoute(const Route& newRoute);
    };

}