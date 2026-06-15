#pragma once
#include "../Core/MapObject.h"
#include "Route.h"

namespace Industry {
    class Mine;
    class Factory;
}

namespace Logistics {

    /**
     * @class Train
     * @brief Klasa bazowa reprezentująca pociąg poruszający się po wyznaczonej trasie.
     * * Dziedziczy po Core::MapObject. Odpowiada za logikę ruchu (w tym tryb Ping-Pong)
     * oraz interakcje załadunku i rozładunku z budynkami przemysłowymi.
     */
    class Train : public Core::MapObject {
    protected:
        int currentCapacity;  ///< Aktualna ilość jednostek surowca w ładowni.
        int maxCapacity; ///< Maksymalna pojemność ładowni pociągu.
        float speed; ///< Prędkość poruszania się pociągu w pikselach na tick.
        Route route; ///< Trasa składająca się z węzłów (punktów docelowych).
        size_t currentWaypointIndex = 0; ///< Indeks węzła na trasie, do którego aktualnie zmierza pociąg.
        bool movingForward = true; ///< Flaga kierunku ruchu: true oznacza jazdę do przodu, false to powrót (bieg wsteczny).
        Core::ResourceType cargoType = Core::ResourceType::Coal; ///< Typ surowca przypisany do danego składu.

    public:
        /**
         * @brief Wirtualny destruktor domyślny.
         */
        virtual ~Train() = default;
        
        /**
         * @brief Rysuje obiekt pociągu w przestrzeni symulacji.
         * @param window Referencja do głównego okna renderowania SFML.
         */
        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Aktualizuje pozycję pociągu na mapie oraz nadzoruje zmianę węzłów trasy.
         */
        void update() override;

        /**
         * @brief Wirtualna metoda polimorficzna dodająca jednostkę surowca do ładowni pociągu.
         * @throw CapacityExceededException Jeśli pojemność pociągu została przekroczona.
         */
        virtual void loadResource();

        /**
         * @brief Przypisuje pociągowi nową trasę i ustawia go na jej pierwszym węźle.
         * @param newRoute Obiekt trasy, po której pociąg będzie się poruszał.
         */
        void setRoute(const Route& newRoute);
        
        /**
         * @brief Próbuje załadować surowiec z kopalni, jeśli pociąg znajduje się w jej zasięgu.
         * @param mine Referencja do obiektu kopalni.
         */
        void loadFromMine(Industry::Mine& mine);

        /**
         * @brief Próbuje załadować gotowy produkt (np. stal) z fabryki.
         * @param factory Referencja do obiektu fabryki posiadającej wyprodukowane dobra.
         */
        void loadFromFactory(Industry::Factory& factory);

        /**
         * @brief Zrzuca posiadany ładunek do buforów wejściowych fabryki.
         * @param factory Referencja do fabryki docelowej.
         * @param toBufferB Flaga określająca, czy surowiec ma trafić do drugiego bufora (np. ruda w hucie). Domyślnie false (bufor A).
         */
        void unloadToFactory(Industry::Factory& factory, bool toBufferB = false);
        
        /**
         * @brief Ustawia rodzaj przewożonego towaru.
         * @param type Typ surowca z enumeratora ResourceType.
         */
        void setCargoType(Core::ResourceType type) { cargoType = type; }

        /**
         * @brief Pobiera informację o typie aktualnie przewożonego ładunku.
         * @return Typ surowca z enumeratora ResourceType.
         */
        Core::ResourceType getCargoType() const { return cargoType; }

        /**
         * @brief Zwraca aktualne zapełnienie pociągu.
         * @return Ilość surowca znajdującego się obecnie w ładowni.
         */
        int getCurrentCapacity() const { return currentCapacity; }

        /**
         * @brief Sprawdza, czy pociąg osiągnął ostatni punkt swojej trasy.
         * @return True, jeśli trasa nie jest pusta i indeks węzła przekroczył liczbę punktów.
         */
        bool isFinished() const { 
            return !route.isEmpty() && currentWaypointIndex >= route.getWaypoints().size(); 
        }
    };
}