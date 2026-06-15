#include "PowerPlant.h"
#include "EmptyStorageException.h"

namespace Industry {

    PowerPlant::PowerPlant() {

    }

void PowerPlant::processResources() {
    consumeInputA(1);
    generatedEnergy += 10; // Każdy węgiel to +10 Energii
}

}