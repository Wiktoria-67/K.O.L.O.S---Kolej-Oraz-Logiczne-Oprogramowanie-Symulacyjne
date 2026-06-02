#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "IDrawable.h"

namespace Core {
    class Renderer {
    private:
        sf::RenderWindow window;
    public:
        void initWindow();
        void renderAll(const std::vector<std::unique_ptr<IDrawable>>& drawables);
        bool isWindowOpen() const;
        void handleEvents();

        sf::RenderWindow& getWindow() { return window; }
    };
}