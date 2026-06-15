#include "MachineFactory.h"
#include "EmptyStorageException.h"

namespace Industry {

    MachineFactory::MachineFactory() {

    }

void MachineFactory::processResources() {

        if (!powerGrid || powerGrid->getGeneratedEnergy() < 10) {
        throw EmptyStorageException(); // Zatrzymuje produkcję z powodu braku zasilania
    }

    consumeInputA(1);

    powerGrid->consumeEnergy(10);

    victoryPoints += 50;
}

}