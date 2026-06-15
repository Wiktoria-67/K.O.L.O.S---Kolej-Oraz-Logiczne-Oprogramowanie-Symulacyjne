#include "SimulationEngine.h"
#include <iostream>

namespace Core {

    SimulationEngine::SimulationEngine() : isRunning(false) {
        // Inicjalizacja bezpiecznego stanu silnika przed startem pętli
        std::cout << "[System] SimulationEngine zainicjalizowany.\n";
    }

    void SimulationEngine::addMapObject(std::unique_ptr<MapObject> obj) {
        // Przejęcie własności wskaźnika za pomocą std::move
        if (obj) {
            simulationObjects.push_back(std::move(obj));
        }
    }

    void SimulationEngine::startSimulation() {
        isRunning = true;
        std::cout << "[System] Startowanie symulacji...\n";
        renderer.initWindow();
    }

    void SimulationEngine::tick() {
        /* * Główna pętla logiczna (tzw. Tick).
         * Iterujemy przez wszystkie obiekty polimorficzne, wywołując ich logikę update().
         */
        for(auto& obj : simulationObjects) {
            obj->update();
        }
    }

}