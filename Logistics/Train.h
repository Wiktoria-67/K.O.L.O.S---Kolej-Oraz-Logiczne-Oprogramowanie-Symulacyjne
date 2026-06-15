#pragma once
#include "../Core/MapObject.h"
#include "Route.h"

// Deklaracje wyprzedzające zapobiegające cyklicznemu dołączaniu nagłówków
namespace Industry {
class Mine;
class Factory;
}

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

        Core::ResourceType cargoType = Core::ResourceType::Coal; ///Typ przewożonego towaru

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


        /**
         * @brief Pobiera surowce z magazynu stacyjnego kopalni.
         * * Logika wykonuje się wyłącznie wtedy, gdy pozycja pociągu pokrywa się z pozycją kopalni.
         * Pętla przeładunkowa pobiera surowce do momentu zapełnienia ładowni pociągu lub opróżnienia kopalni.
         * @param mine Referencja do kopalni, z której pociąg próbuje podjąć towar.
         */
        void loadFromMine(Industry::Mine& mine);

        /**
         * @brief Rozładowuje wszystkie przewożone surowce do bufora wejściowego wskazanej fabryki.
         * * Logika wykonuje się wyłącznie wtedy, gdy pociąg znajduje się dokładnie na pozycji fabryki.
         * Czyści ładownię pociągu do zera, dystrybuując zasoby do odpowiedniego magazynu fabrycznego.
         * @param factory Referencja do fabryki docelowej.
         * @param toBufferB Flaga określająca, czy towar ma trafić do dodatkowego bufora B (domyślnie false - bufor podstawowy A).
         */
        void unloadToFactory(Industry::Factory& factory, bool toBufferB = false);

        /**
         * @brief Konfiguruje lub zmienia dedykowany typ surowca, jaki pociąg ma prawo transportować.
         * @param type Wybrany surowiec z bezpiecznego enuma Core::ResourceType.
         */
        void setCargoType(Core::ResourceType type) { cargoType = type; }

        /**
         * @brief Pobiera aktualny typ surowca, jaki pociąg jest skonfigurowany przewozić.
         * @return Obiekt enum reprezentujący przypisany typ towaru.
         */
        Core::ResourceType getCargoType() const { return cargoType; }

        /**
         * @brief Pobiera bieżący stan zapełnienia ładowni pociągu.
         * @return Liczba sztuk aktualnie transportowanego surowca.
         */
        int getCurrentCapacity() const { return currentCapacity; }
    };

}