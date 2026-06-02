#include "Factory.h"
#include "EmptyStorageException.h"
#include <iostream>

namespace Industry {

    void Factory::draw(sf::RenderWindow& window) {
        sf::RectangleShape rect({40.f, 40.f});
        rect.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
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
                      << position.x << ", Y:" << position.y << "\n";
        } 
        catch (const EmptyStorageException& e) {
            // Fabryka stoi w miejscu
        }
    }

}