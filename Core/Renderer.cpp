// Renderer.cpp
#include "Renderer.h"
#include "RenderException.h"
#include <iostream>
#include <optional>

namespace Core {

    void Renderer::initWindow() {
        // Konfiguracja okna SFML
        window.create(sf::VideoMode({800, 600}), "K.O.L.O.S. - Symulacja");
        window.setFramerateLimit(60);
    }

    void Renderer::renderAll(const std::vector<std::unique_ptr<IDrawable>>& drawables) {
        window.clear(sf::Color(40, 40, 40));

        // Rysowanie wszystkich zarejestrowanych obiektów implementujących IDrawable
        for (const auto& drawable : drawables) {
            drawable->draw(window);
        }

        window.display();
    }

    bool Renderer::isWindowOpen() const {
        return window.isOpen();
    }

    void Renderer::handleEvents() {
        // Obsługa zdarzeń okna systemu operacyjnego
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
        }
    }

}