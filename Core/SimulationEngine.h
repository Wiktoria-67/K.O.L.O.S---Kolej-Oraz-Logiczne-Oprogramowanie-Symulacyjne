#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"
#include "Renderer.h"

namespace Core {
    class SimulationEngine {
    private:
        std::vector<std::unique_ptr<MapObject>> simulationObjects;
        Renderer renderer;
        bool isRunning;
    public:
        SimulationEngine();
        void startSimulation();
        void tick(); 
    };
}