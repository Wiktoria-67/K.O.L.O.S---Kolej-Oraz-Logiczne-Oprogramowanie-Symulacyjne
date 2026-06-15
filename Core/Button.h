#pragma once
#include "UIElement.h"
#include <string>
#include <optional>

namespace Core {

    /**
     * @class Button
     * @brief Reprezentuje interaktywny przycisk na ekranie.
     */
    class Button : public UIElement {
    private:
        sf::Color buttonColor; ///< Kolor wypełnienia przycisku.
        sf::Font font;   ///< Obiekt czcionki
        std::optional<sf::Text> text;
    public:
        /**
         * @brief Inicjalizuje przycisk o określonych wymiarach i wyglądzie.
         * @param x Współrzędna X (lewy górny róg).
         * @param y Współrzędna Y (lewy górny róg).
         * @param w Szerokość przycisku.
         * @param h Wysokość przycisku.
         * @param color Kolor bazowy przycisku z biblioteki SFML.
         * @param labelText Tekst nagit status przycisku z biblioteki SFML.
         */
        Button(int x, int y, int w, int h, sf::Color color, const std::string& labelText);

        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Weryfikuje zderzenie kursora z hitboxem przycisku.
         */
        bool onClick(int mouseX, int mouseY) override;
    };
}