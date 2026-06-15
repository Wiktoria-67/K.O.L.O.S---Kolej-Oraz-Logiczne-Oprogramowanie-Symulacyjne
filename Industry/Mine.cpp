#include "Mine.h"

namespace Industry {

    void Mine::draw(sf::RenderWindow& window) {
        sf::RectangleShape rect({40.f, 40.f});
        rect.setPosition({static_cast<float>(getPosition().x), static_cast<float>(getPosition().y)});
        rect.setFillColor(objectColor);
        rect.setOutlineThickness(1.f);
        rect.setOutlineColor(sf::Color::White);
        window.draw(rect);
    }

    void Mine::update() {
        // Główna pętla odliczająca czas do wykopania surowca
        if (resourceTimer > 0) {
            resourceTimer--;
        } else {
            generateResource(); 
            resourceTimer = 100; 
        }
    }

}