#include "SimulationEngine.h"
#include <iostream> // Tylko do testowych logów

namespace Core {

    // Definicja konstruktora
    SimulationEngine::SimulationEngine() : isRunning(false) {
        std::cout << "[System] SimulationEngine zainicjalizowany.\n";
    }

    // Definicja metody startSimulation
    void SimulationEngine::startSimulation() {
        isRunning = true;
        std::cout << "[System] Startowanie symulacji...\n";
        
        renderer.initWindow();

        // Tu docelowo znajdzie się główna pętla programu
        // while (isRunning) { tick(); }
    }

    // Definicja metody tick (pojedynczy krok czasu)
    void SimulationEngine::tick() {
        // 1. Aktualizacja logiki wszystkich obiektów
        for(auto& obj : simulationObjects) {
            obj->update();
        }

        // 2. Renderowanie klatki (przygotowanie wektora do rysowania)
        // Wymaga rzutowania wskaźników lub odpowiedniej struktury, 
        // to zrobicie w kolejnym etapie prac nad Rendererem.
        
        std::cout << "[System] Tick wykonany.\n";
    }

} // namespace Core