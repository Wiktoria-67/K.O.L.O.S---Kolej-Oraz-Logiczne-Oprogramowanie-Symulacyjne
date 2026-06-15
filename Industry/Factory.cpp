#include "Factory.h"
#include "EmptyStorageException.h"
#include <iostream>

namespace Industry {

    void Factory::draw(sf::RenderWindow& window) {
        sf::RectangleShape rect({40.f, 40.f});
        rect.setPosition({static_cast<float>(getPosition().x), static_cast<float>(getPosition().y)});
        rect.setFillColor(sf::Color(70, 100, 150));
        rect.setOutlineThickness(1.f);
        rect.setOutlineColor(sf::Color::White);
        window.draw(rect);
    }

    void Factory::update() {
        try {
            processResources();
            // Jeśli nie rzuci wyjątku (ma surowce i pracuje):
            std::cout << "[Factory] Przetwarzam surowce na pozycji X:" 
                      << getPosition().x << ", Y:" << getPosition().y << "\n";
        } 
        catch (const EmptyStorageException& e) {
            // Fabryka stoi w miejscu
        }
    }


    // Gwarantuje, że nie dodamy ujemnej liczby surowców
    void Factory::addInputA(int amount) {
        if (amount > 0) {
            inputBufferA += amount;
        }
    }

    void Factory::addInputB(int amount) {
        if (amount > 0) {
            inputBufferB += amount;
        }
    }

    // Walidacja logiczna: jeśli brakuje surowców, od razu rzucamy wyjątek
    void Factory::consumeInputA(int amount) {
        if (inputBufferA < amount) {
            throw EmptyStorageException();
        }
        inputBufferA -= amount;
    }

    void Factory::consumeInputB(int amount) {
        if (inputBufferB < amount) {
            throw EmptyStorageException();
        }
        inputBufferB -= amount;
    }

}