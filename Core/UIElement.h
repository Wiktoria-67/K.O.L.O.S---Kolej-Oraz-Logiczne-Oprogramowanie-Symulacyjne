#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include "IClickable.h"
#include "SharedTypes.h"

namespace Core {
    class UIElement : public IDrawable, public IClickable {
    protected:
        Point2D position;
        int width;
        int height;
    public:
        virtual ~UIElement() = default;
        void draw(sf::RenderWindow& window) override = 0; // <-- TUTAJ zmiana
        bool onClick(int mouseX, int mouseY) override = 0;
    };
}