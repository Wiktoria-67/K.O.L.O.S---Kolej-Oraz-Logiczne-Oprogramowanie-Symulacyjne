#include "SteelMill.h"
#include "EmptyStorageException.h"

namespace Industry {

    SteelMill::SteelMill() {

    }

void SteelMill::processResources() {
    if (getInputBufferA() < 1 || getInputBufferB() < 1) {
        throw EmptyStorageException();
    }
    consumeInputA(1);
    consumeInputB(1);
    
    // Huta zjadła węgiel i rudę, więc produkuje 1 sztukę stali!
    increaseOutputBuffer(1); 
}

}