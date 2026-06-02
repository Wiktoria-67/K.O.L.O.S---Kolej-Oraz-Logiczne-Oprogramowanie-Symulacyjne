#include "Train.h"
#include "CapacityExceededException.h"
#include <iostream>

namespace Logistics {

    void Train::draw() {
        // Docelowo tutaj podepniecie wywołania z Waszego frameworka okienkowego (np. Qt lub SFML)
        // Na etap 0.5 (Kamień Milowy 1) logujemy tylko akcję
        std::cout << "[Renderer] Rysowanie pociagu...\n";
    }

    void Train::update() {
        // Podstawowa logika przemieszczania realizowana w każdym ticku symulacji
        std::cout << "[Engine] Aktualizacja pozycji pociagu...\n";
    }

    void Train::loadResource() {
        // Sprawdzenie przepustowości zgodnie z założeniami projektu
        if (currentCapacity >= maxCapacity) {
            throw CapacityExceededException();
        }
        
        currentCapacity++;
        std::cout << "Zaladowano surowiec. Aktualny stan ładowni: " 
                  << currentCapacity << "/" << maxCapacity << "\n";
    }

} // namespace Logistics