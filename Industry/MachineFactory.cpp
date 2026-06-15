#include "MachineFactory.h"
#include "EmptyStorageException.h"

namespace Industry {

    MachineFactory::MachineFactory() {

    }

void MachineFactory::processResources() {
    consumeInputA(1); 
    victoryPoints += 50; 
}

}