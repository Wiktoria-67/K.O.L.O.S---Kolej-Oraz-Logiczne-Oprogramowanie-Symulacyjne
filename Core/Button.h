#pragma once
#include "UIElement.h"
#include <string>

namespace Core {

    /**
     * @class Button
     * @brief Reprezentuje interaktywny przycisk na ekranie.
     */
    class Button : public UIElement {
    private:
        sf::Color buttonColor; ///< Kolor wypełnienia przycisku.
    public:
        /**
         * @brief Inicjalizuje przycisk o określonych wymiarach i wyglądzie.
         * @param x Współrzędna X (lewy górny róg).
         * @param y Współrzędna Y (lewy górny róg).
         * @param w Szerokość przycisku.
         * @param h Wysokość przycisku.
         * @param color Kolor bazowy przycisku z biblioteki SFML.
         */
        Button(int x, int y, int w, int h, sf::Color color);

        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Weryfikuje zderzenie kursora z hitboxem przycisku.
         */
        bool onClick(int mouseX, int mouseY) override;
    };
}