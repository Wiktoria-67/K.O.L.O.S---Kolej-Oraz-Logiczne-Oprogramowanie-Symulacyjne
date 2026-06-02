#pragma once
#include "UIElement.h"

namespace Core {
    class InfoPanel : public UIElement {
    public:
        void draw(sf::RenderWindow& window) override;
        bool onClick(int mouseX, int mouseY) override;
        void updateDisplayData();
    };
}