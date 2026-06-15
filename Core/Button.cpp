#include "Button.h"
#include <iostream>

namespace Core {

    Button::Button(int x, int y, int w, int h, sf::Color color, const std::string& labelText) {
        position = {x, y};
        width = w;
        height = h;
        buttonColor = color;

        // 1. Ładowanie czcionki
        if (!font.openFromFile("assets/font.ttf")) {
            std::cerr << "[Blad] Nie znaleziono pliku assets/font.ttf!\n";
        }

        // 2. Inicjalizacja tekstu po załadowaniu czcionki (Wymóg SFML 3)
        // Konstruktor Text w SFML 3: sf::Text(font, string, characterSize)
        text.emplace(font, labelText, 16);
        text->setFillColor(sf::Color::White);

        // 3. Centrowanie przy użyciu  składni sf::FloatRect
        sf::FloatRect textRect = text->getLocalBounds();

        text->setOrigin({textRect.size.x / 2.0f, textRect.size.y / 2.0f});
        text->setPosition({position.x + width / 2.0f, position.y + height / 2.0f - textRect.position.y});
    }

    void Button::draw(sf::RenderWindow& window) {
        // Rysowanie prostokątnego kształtu przycisku z ramką
        sf::RectangleShape rect({static_cast<float>(width), static_cast<float>(height)}); 
        rect.setPosition({static_cast<float>(position.x), static_cast<float>(position.y)});
        rect.setFillColor(buttonColor);
        rect.setOutlineThickness(2.0f);
        rect.setOutlineColor(sf::Color::White);

        window.draw(rect);
        if (text) {
            window.draw(*text);
        }
    }

    bool Button::onClick(int mouseX, int mouseY) {
        /* * Weryfikacja typu AABB (Axis-Aligned Bounding Box).
         * Sprawdza, czy punkt kliknięcia zawiera się w obszarze przycisku.
         */
        if (mouseX >= position.x && mouseX <= position.x + width &&
            mouseY >= position.y && mouseY <= position.y + height) {
            return true;
        }
        return false;
    }

}