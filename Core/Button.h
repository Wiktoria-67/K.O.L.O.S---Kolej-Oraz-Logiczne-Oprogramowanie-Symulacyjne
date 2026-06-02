#pragma once
#include "UIElement.h"
#include <string>

namespace Core {
    class Button : public UIElement {
    private:
        sf::Color buttonColor;
    public:
        Button(int x, int y, int w, int h, sf::Color color);

        void draw(sf::RenderWindow& window) override;
        bool onClick(int mouseX, int mouseY) override;
    };
}