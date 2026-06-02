#include "SimulationEngine.h"
#include <iostream>

namespace Core {

    SimulationEngine::SimulationEngine() : isRunning(false) {
        std::cout << "[System] SimulationEngine zainicjalizowany.\n";
    }

    void SimulationEngine::addMapObject(std::unique_ptr<MapObject> obj) {
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
        // Aktualizacja logiki wszystkich dodanych do silnika obiektów
        for(auto& obj : simulationObjects) {
            obj->update();
        }
    }

}