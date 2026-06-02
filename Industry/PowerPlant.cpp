#include "PowerPlant.h"
#include "EmptyStorageException.h"

namespace Industry {

    PowerPlant::PowerPlant() {
        inputBufferA = 0; // Stan początkowy węgla
        inputBufferB = 0; // Nieużywane w elektrowni
    }

    void PowerPlant::processResources() {
        if (inputBufferA <= 0) {
            throw EmptyStorageException(); // Zgłoszenie błędu, jeśli nie ma węgla
        }
        
        // Konsumpcja węgla
        inputBufferA--;
        
        // Tutaj logika np. dodawania globalnych punktów energii
    }

}