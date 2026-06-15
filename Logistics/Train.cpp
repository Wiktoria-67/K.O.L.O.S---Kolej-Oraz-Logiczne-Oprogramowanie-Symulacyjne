#include "Train.h"
#include "CapacityExceededException.h"
#include <iostream>
#include <cmath>
#include "../Industry/Mine.h"
#include "../Industry/Factory.h"

namespace Logistics {

    void Train::draw(sf::RenderWindow& window) {
        std::cout << "[Renderer] Rysowanie pociagu (X:" << getPosition().x << ", Y:" << getPosition().y << ")\n";
    }

    void Train::setRoute(const Route& newRoute) {
        route = newRoute;
        currentWaypointIndex = 0;
        
        // Jeśli trasa nie jest pusta, od razu ustawiamy pociąg na stacji początkowej
        if (!route.isEmpty()) {
            setPosition(route.getWaypoints().front());
        }
    }

    void Train::update() {
        /* * Główna logika ruchu pociągu:
         * 1. Pobiera punkt docelowy z trasy.
         * 2. Porównuje aktualną pozycję z celem (wektor przesunięcia).
         * 3. Jeśli odległość <= prędkość, "teleportuje" do punktu i przechodzi do kolejnego.
         * 4. W przeciwnym razie aktualizuje pozycję o wartość wektora prędkości.
         */
        if (route.isEmpty() || currentWaypointIndex >= route.getWaypoints().size()) {
            return; 
        }

        Core::Point2D target = route.getWaypoints()[currentWaypointIndex];

        int dx = target.x - getPosition().x;
        int dy = target.y - getPosition().y;

        // Sprawdzenie, czy jesteśmy wystarczająco blisko celu (tolerancja na prędkość)
        // Jeśli jesteśmy na tyle blisko, że w następnym ticku przekroczylibyśmy cel, po prostu "cumujemy" na stacji
        if (std::abs(dx) <= static_cast<int>(speed) && std::abs(dy) <= static_cast<int>(speed)) {
            setPosition(target);
            currentWaypointIndex++;
            
            std::cout << "[Logistics] Pociag osiagnal wezel trasy (X: " 
                      << getPosition().x << ", Y: " << getPosition().y << ").\n";
        } else {

            Core::Point2D currentPos = getPosition();

            // Ruch w stronę punktu docelowego
            if (dx > 0) currentPos.x += static_cast<int>(speed);
            else if (dx < 0) currentPos.x -= static_cast<int>(speed);

            if (dy > 0) currentPos.y += static_cast<int>(speed);
            else if (dy < 0) currentPos.y -= static_cast<int>(speed);

            setPosition(currentPos);

            std::cout << "[Logistics] Pociag w trasie... Pozycja: " 
                      << getPosition().x << ", " << getPosition().y << "\n";
        }
    }

    void Train::loadResource() {
        // Logika ładowania surowców
        if (currentCapacity >= maxCapacity) {
            throw CapacityExceededException();
        }
        currentCapacity++;
        std::cout << "Zaladowano surowiec. Aktualny stan ładowni: " 
                  << currentCapacity << "/" << maxCapacity << "\n";
    }

    void Train::loadFromMine(Industry::Mine& mine) {
        // Pociąg ładuje tylko wtedy, gdy stoi dokładnie w miejscu kopalni
        if (getPosition() == mine.getPosition()) {
            // Ładujemy dopóki pociąg ma miejsce, a kopalnia ma surowce
            while (currentCapacity < maxCapacity && mine.getOutputBuffer() > 0) {
                try {
                    loadResource(); // Wywołanie polimorficzne z komunikatami specyficznymi dla typu pociągu
                    mine.decreaseOutputBuffer(1); // Pobranie z kopalni
                }
                catch (const CapacityExceededException& e) {
                    break; // Ładownia pełna, przerywamy pętlę bezpiecznie
                }
            }
        }
    }

    void Train::unloadToFactory(Industry::Factory& factory, bool toBufferB) {
        // Pociąg rozładowuje surowce tylko na pozycji fabryki
        if (getPosition() == factory.getPosition()) {
            int unloadedAmount = 0;
            while (currentCapacity > 0) {
                if (toBufferB) {
                    factory.addInputB(1);
                } else {
                    factory.addInputA(1);
                }
                currentCapacity--;
                unloadedAmount++;
            }
            if (unloadedAmount > 0) {
                std::cout << "[Logistics] Rozladowano " << unloadedAmount
                          << " jednostek surowca w fabryce.\n";
            }
        }
    }

} // namespace Logistics