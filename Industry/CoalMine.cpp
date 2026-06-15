#include "CoalMine.h"
#include <iostream>

namespace Industry {

    CoalMine::CoalMine() {
        resourceTimer = 50; // Węgiel wydobywa się np. co 50 ticków
    }

    void CoalMine::generateResource() {
        // Logika dodania nowej jednostki węgla do bufora wyjściowego kopalni
        increaseOutputBuffer(1); // Dodanie węgla do bufora
        std::cout << "[CoalMine] Wykopano wegiel! Stan magazynu: " << getOutputBuffer() << "\n";
    }

}