#include "SteelMill.h"
#include "EmptyStorageException.h"

namespace Industry {

    SteelMill::SteelMill() {

    }

    void SteelMill::processResources() {
        // Huta wymaga obu surowców do wyprodukowania stali
        if (getInputBufferA() < 1 || getInputBufferB() < 1) {
            throw EmptyStorageException();
        }

        consumeInputA(1);
        consumeInputB(1);

        // Logika dodania gotowej stali do bufora wyjściowego (dla pociągów)
    }

}