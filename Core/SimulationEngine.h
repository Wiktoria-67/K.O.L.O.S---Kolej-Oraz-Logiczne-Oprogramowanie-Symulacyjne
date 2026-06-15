#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"
#include "Renderer.h"

namespace Core {
    /**
     * @class SimulationEngine
     * @brief Rdzeń architektoniczny zarządzający całym cyklem życia aplikacji.
     * * Hermetyzuje obiekty mapy, posiada instancję renderera oraz kontroluje przepływ czasu.
     */
    class SimulationEngine {
    private:
        std::vector<std::unique_ptr<MapObject>> simulationObjects; ///< Kontener przechowujący wszystkie byty przestrzenne w grze.
        Renderer renderer; ///< Wewnętrzny moduł wyświetlający grafikę.
        bool isRunning; ///< Flaga wskazująca, czy główna pętla programu jest aktywna.
    public:
        /**
         * @brief Konstruktor silnika. Ustawia początkowy stan bezpieczny.
         */
        SimulationEngine();

        /**
         * @brief Uruchamia silnik, otwiera okno systemowe i podnosi flagę isRunning.
         */
        void startSimulation();

        /**
         * @brief Wykonuje pojedynczą klatkę logiki, iterując przez wszystkie dodane obiekty.
         */
        void tick();
        
        /**
         * @brief Odbiera na własność obiekt przestrzenny i rejestruje go w pętli symulacji.
         * @param obj Unikalny wskaźnik na instancję dziedziczącą po MapObject.
         */
        void addMapObject(std::unique_ptr<MapObject> obj); 
    };
}