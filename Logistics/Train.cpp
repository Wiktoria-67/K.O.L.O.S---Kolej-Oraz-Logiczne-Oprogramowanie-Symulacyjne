#include "Train.h"
#include "CapacityExceededException.h"
#include <iostream>
#include <cmath>
#include "../Industry/Mine.h"
#include "../Industry/Factory.h"

namespace Logistics {

    void Train::draw(sf::RenderWindow& window) {
        //std::cout << "[Renderer] Rysowanie pociagu (X:" << getPosition().x << ", Y:" << getPosition().y << ")\n";
        // Fizyczne rysowanie pociągu w oknie SFML
        sf::RectangleShape rect({20.f, 20.f}); // Pociąg jest mniejszy (20x20) niż budynki (40x40)

        // Ustawiamy pozycję, rzutując współrzędne logiczne na float dla SFML
        rect.setPosition({static_cast<float>(getPosition().x), static_cast<float>(getPosition().y)});

        // Pociąg będzie miał charakterystyczny, żółto-pomarańczowy kolor, by odznaczał się na tle mapy
        rect.setFillColor(sf::Color(200, 150, 50));
        rect.setOutlineThickness(1.f);
        rect.setOutlineColor(sf::Color::White);

        // Zlecenie narysowania obiektu do karty graficznej
        window.draw(rect);
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
        if (route.isEmpty()) {
            return;
        }

        Core::Point2D target = route.getWaypoints()[currentWaypointIndex];

        int dx = target.x - getPosition().x;
        int dy = target.y - getPosition().y;

        if (std::abs(dx) <= static_cast<int>(speed) && std::abs(dy) <= static_cast<int>(speed)) {
            setPosition(target);

            std::cout << "[Logistics] Pociag osiagnal wezel trasy (X: "
                      << getPosition().x << ", Y: " << getPosition().y << ").\n";

            if (movingForward) {
                if (currentWaypointIndex + 1 < route.getWaypoints().size()) {
                    currentWaypointIndex++;
                } else {
                    movingForward = false;
                    if (currentWaypointIndex > 0) {
                        currentWaypointIndex--;
                    }
                }
            } else {
                if (currentWaypointIndex > 0) {
                    currentWaypointIndex--;
                } else {
                    movingForward = true;
                    if (currentWaypointIndex + 1 < route.getWaypoints().size()) {
                        currentWaypointIndex++;
                    }
                }
            }
        } else {
            Core::Point2D currentPos = getPosition();

            if (dx > 0) currentPos.x += static_cast<int>(speed);
            else if (dx < 0) currentPos.x -= static_cast<int>(speed);

            if (dy > 0) currentPos.y += static_cast<int>(speed);
            else if (dy < 0) currentPos.y -= static_cast<int>(speed);

            setPosition(currentPos);
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
        // Obliczamy odległość od kopalni
        int dx = std::abs(getPosition().x - mine.getPosition().x);
        int dy = std::abs(getPosition().y - mine.getPosition().y);
        // Hitbox: Pociąg podejmuje akcję tylko, jeśli jest w promieniu 30 pikseli
        if (dx <= 50 && dy <= 50) {
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
        // Obliczamy odległość od fabryki
        int dx = std::abs(getPosition().x - factory.getPosition().x);
        int dy = std::abs(getPosition().y - factory.getPosition().y);
        // Hitbox: Pociąg zrzuca towar tylko, jeśli jest w promieniu 30 pikseli
        if (dx <= 50 && dy <= 50) {
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

void Train::loadFromFactory(Industry::Factory& factory) {
        int dx = std::abs(getPosition().x - factory.getPosition().x);
        int dy = std::abs(getPosition().y - factory.getPosition().y);

        // Hitbox: Pociąg ładuje stal, jeśli jest na stacji
        if (dx <= 50 && dy <= 50) {
            while (currentCapacity < maxCapacity && factory.getOutputBuffer() > 0) {
                try {
                    loadResource(); 
                    factory.decreaseOutputBuffer(1); // Zabranie stali z Huty
                } catch (const CapacityExceededException& e) {
                    break; 
                }
            }
        }
    }

} // namespace Logistics