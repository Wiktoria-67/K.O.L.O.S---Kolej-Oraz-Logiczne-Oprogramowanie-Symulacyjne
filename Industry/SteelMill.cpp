#include "SteelMill.h"
#include "EmptyStorageException.h"

namespace Industry {

    SteelMill::SteelMill() {
        inputBufferA = 0; // Bufor na Węgiel
        inputBufferB = 0; // Bufor na Rudę Żelaza
    }

    void SteelMill::processResources() {
        // Huta wymaga obu surowców do wyprodukowania stali
        if (inputBufferA <= 0 || inputBufferB <= 0) {
            throw EmptyStorageException();
        }

        // Konsumpcja surowców wejściowych
        inputBufferA--;
        inputBufferB--;

        // Logika dodania gotowej stali do bufora wyjściowego (dla pociągów)
    }

}