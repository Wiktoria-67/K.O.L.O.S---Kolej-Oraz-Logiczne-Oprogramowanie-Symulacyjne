#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"
#include "../Logistics/TrackNetwork.h"
#include "../Logistics/Route.h"

// Deklaracje zapowiadające
namespace Industry {
class CoalMine; class IronMine; class SteelMill; class PowerPlant; class MachineFactory;
}

namespace Core {
class SimulationEngine {
public:
    // Główne kontenery symulacji
    std::vector<std::unique_ptr<MapObject>> mapObjects;
    Logistics::TrackNetwork trackNetwork;
    std::vector<Logistics::Route> allRoutes;
    long long tickCounter = 0;

    // Wskaźniki na obiekty infrastruktury
    Industry::CoalMine* pointerToCoalMine = nullptr;
    Industry::IronMine* pointerToIronMine = nullptr;
    Industry::SteelMill* pointerToFactory = nullptr;
    Industry::PowerPlant* pointerToPowerPlant = nullptr;
    Industry::MachineFactory* pointerToMachineFactory = nullptr;

    SimulationEngine() = default;

    // Pojedynczy krok logiki symulacji (dawne obliczenia z pętli main)
    void tick();
};
}