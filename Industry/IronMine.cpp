#include <iostream>
#include "IronMine.h"

namespace Industry {

    IronMine::IronMine() {
        resourceTimer = 80; // Ruda żelaza wydobywa się wolniej (co 80 ticków)
    }

    void IronMine::generateResource() {
        // Logika dodania nowej jednostki rudy żelaza do bufora wyjściowego kopalni
        increaseOutputBuffer(1); // Dodanie rudy do bufora
        std::cout << "[IronMine] Wykopano rude zelaza! Stan magazynu: " << getOutputBuffer() << "\n";
    }

}