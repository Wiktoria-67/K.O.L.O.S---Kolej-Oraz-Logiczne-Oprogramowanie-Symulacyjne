#include "MachineFactory.h"
#include "EmptyStorageException.h"

namespace Industry {

    MachineFactory::MachineFactory() {
        inputBufferA = 0; // Bufor na Stal
        inputBufferB = 0; // Ewentualny inny surowiec
    }

    void MachineFactory::processResources() {
        if (inputBufferA <= 0) {
            throw EmptyStorageException();
        }

        inputBufferA--;

        // Logika generowania punktów zwycięstwa / finalnych produktów
    }

}