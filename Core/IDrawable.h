#pragma once
#include <SFML/Graphics.hpp>

namespace Core {
    class IDrawable {
    public:
        virtual ~IDrawable() = default;
        virtual void draw(sf::RenderWindow& window) = 0;
    };
}