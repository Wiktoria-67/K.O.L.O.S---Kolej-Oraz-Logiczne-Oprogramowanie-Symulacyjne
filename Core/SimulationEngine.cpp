#include "SimulationEngine.h"
#include "../Industry/CoalMine.h"
#include "../Industry/IronMine.h"
#include "../Industry/SteelMill.h"
#include "../Industry/PowerPlant.h"
#include "../Industry/MachineFactory.h"
#include "../Logistics/Train.h"
#include "../Logistics/CollisionException.h"

namespace Core {

void SimulationEngine::tick() {
    tickCounter++;

    // 1. Sprawdzanie kolizji
    try {
        trackNetwork.checkCollisions();
    } catch (const Logistics::CollisionException& e) {
        // Gramy dalej pomimo kolizji
    }

    // 2. Aktualizacja budynków
    for (const auto& obj : mapObjects) {
        if (dynamic_cast<Industry::IronMine*>(obj.get()) && tickCounter % 2 == 0) {
            continue;
        }
        obj->update();
    }

    // 3. Logika pociągów i wymiany surowców
    for (const auto& obj : mapObjects) {
        if (auto* train = dynamic_cast<Logistics::Train*>(obj.get())) {
            auto cargo = train->getCargoType();

            for (const auto& targetObj : mapObjects) {
                if (cargo == Core::ResourceType::Coal) {
                    if (auto* mine = dynamic_cast<Industry::CoalMine*>(targetObj.get())) train->loadFromMine(*mine);
                    if (auto* mill = dynamic_cast<Industry::SteelMill*>(targetObj.get())) train->unloadToFactory(*mill, false);
                    if (auto* plant = dynamic_cast<Industry::PowerPlant*>(targetObj.get())) train->unloadToFactory(*plant, false);
                }
                else if (cargo == Core::ResourceType::IronOre) {
                    if (auto* mine = dynamic_cast<Industry::IronMine*>(targetObj.get())) train->loadFromMine(*mine);
                    if (auto* mill = dynamic_cast<Industry::SteelMill*>(targetObj.get())) train->unloadToFactory(*mill, true);
                }
                else if (cargo == Core::ResourceType::Steel) {
                    if (auto* mill = dynamic_cast<Industry::SteelMill*>(targetObj.get())) train->loadFromFactory(*mill);
                    if (auto* mFact = dynamic_cast<Industry::MachineFactory*>(targetObj.get())) train->unloadToFactory(*mFact, false);
                }
            }
        }
    }
}

}