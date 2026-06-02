#include "Button.h"
#include <iostream>

namespace Core {

    Button::Button(int x, int y, int w, int h, sf::Color color) {
        position = {x, y};
        width = w;
        height = h;
        buttonColor = color;
    }

    void Button::draw(sf::RenderWindow& window) {
        sf::RectangleShape rect({static_cast<float>(width), static_cast<float>(height)}); 
        rect.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
        rect.setFillColor(buttonColor);
        rect.setOutlineThickness(2.0f);
        rect.setOutlineColor(sf::Color::White);

        window.draw(rect);
    }

    bool Button::onClick(int mouseX, int mouseY) {
        // Sprawdzamy, czy współrzędne myszy zawierają się w prostokącie przycisku
        if (mouseX >= position.x && mouseX <= position.x + width &&
            mouseY >= position.y && mouseY <= position.y + height) {
            return true; // Kliknięto wewnątrz przycisku!
        }
        return false;
    }

}