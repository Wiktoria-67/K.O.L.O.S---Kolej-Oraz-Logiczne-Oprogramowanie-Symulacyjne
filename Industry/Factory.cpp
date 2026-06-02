#include "Factory.h"
#include "EmptyStorageException.h"
#include <iostream>

namespace Industry {

    void Factory::draw() {
        // Docelowo: Rysowanie budynku fabryki na mapie
    }


    // Fragment Industry/Factory.cpp
    void Factory::update() {
        try {
            processResources();
            // Jeśli nie rzuci wyjątku (ma surowce i pracuje):
            std::cout << "[Factory] Przetwarzam surowce na pozycji X:" 
                      << position.x << ", Y:" << position.y << "\n";
        } 
        catch (const EmptyStorageException& e) {
            // Fabryka stoi w miejscu
        }
    }

} // namespace Industry