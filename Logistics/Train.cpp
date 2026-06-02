#include "Train.h"
#include "CapacityExceededException.h"
#include <iostream>
#include <cmath> // Wymagane dla std::abs

namespace Logistics {

    void Train::draw() {
        std::cout << "[Renderer] Rysowanie pociagu (X:" << position.x << ", Y:" << position.y << ")\n";
    }

    void Train::setRoute(const Route& newRoute) {
        route = newRoute;
        currentWaypointIndex = 0;
        
        // Jeśli trasa nie jest pusta, od razu ustawiamy pociąg na stacji początkowej
        if (!route.isEmpty()) {
            position = route.getWaypoints().front();
        }
    }

    void Train::update() {
        // Zabezpieczenie: jeśli trasa jest pusta lub dojechaliśmy do końca
        if (route.isEmpty() || currentWaypointIndex >= route.getWaypoints().size()) {
            return; 
        }

        Core::Point2D target = route.getWaypoints()[currentWaypointIndex];

        int dx = target.x - position.x;
        int dy = target.y - position.y;

        // Sprawdzenie, czy jesteśmy wystarczająco blisko celu (tolerancja na prędkość)
        if (std::abs(dx) <= speed && std::abs(dy) <= speed) {
            position = target;
            currentWaypointIndex++;
            
            std::cout << "[Logistics] Pociag osiagnal wezel trasy (X: " 
                      << position.x << ", Y: " << position.y << ").\n";
        } else {
            // Ruch w stronę punktu docelowego
            if (dx > 0) position.x += static_cast<int>(speed);
            else if (dx < 0) position.x -= static_cast<int>(speed);

            if (dy > 0) position.y += static_cast<int>(speed);
            else if (dy < 0) position.y -= static_cast<int>(speed);

            std::cout << "[Logistics] Pociag w trasie... Pozycja: " 
                      << position.x << ", " << position.y << "\n";
        }
    }

    void Train::loadResource() {
        if (currentCapacity >= maxCapacity) {
            throw CapacityExceededException();
        }
        currentCapacity++;
        std::cout << "Zaladowano surowiec. Aktualny stan ładowni: " 
                  << currentCapacity << "/" << maxCapacity << "\n";
    }

} // namespace Logistics