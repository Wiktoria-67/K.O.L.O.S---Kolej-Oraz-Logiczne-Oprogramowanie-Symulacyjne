#include "PowerPlant.h"
#include "EmptyStorageException.h"

namespace Industry {

    PowerPlant::PowerPlant() {

    }

    void PowerPlant::processResources() {
        consumeInputA(1);
    }

}