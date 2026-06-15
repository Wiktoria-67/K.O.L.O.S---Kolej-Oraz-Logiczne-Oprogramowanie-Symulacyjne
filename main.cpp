#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Core/Renderer.h"
#include "Core/Button.h"
#include "Core/IDrawable.h"
#include "Core/MapObject.h"
#include "Industry/CoalMine.h"
#include "Industry/SteelMill.h"

enum class BuildMode {
    None,
    Mine,
    Factory
};



int main() {
    std::cout << "==================================================\n";
    std::cout << "   K.O.L.O.S. - Edytor Mapy \n";
    std::cout << "==================================================\n\n";

    // 1. Inicjalizacja okna graficznego przez Renderer
    Core::Renderer renderer;
    renderer.initWindow();

    // Pobieramy referencję do okna, żeby nasza pętla mogła z niego czytać eventy
    sf::RenderWindow& window = renderer.getWindow();

    // Przygotowanie paska bocznego
    sf::RectangleShape sidebarPanel({200.f, 600.f});
    sidebarPanel.setFillColor(sf::Color(60, 60, 60));

    std::vector<std::unique_ptr<Core::Button>> guiButtons;
    std::vector<std::unique_ptr<Core::MapObject>> mapObjects;

    guiButtons.push_back(std::make_unique<Core::Button>(20, 50, 160, 40, sf::Color(180, 70, 70)));   // Kopalnia
    guiButtons.push_back(std::make_unique<Core::Button>(20, 110, 160, 40, sf::Color(70, 70, 180)));  // Huta

    BuildMode currentBuildMode = BuildMode::None;

    // Główna pętla programu
    while (window.isOpen()) {
        
        // Obsługa zdarzeń
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                if (mousePressed->button == sf::Mouse::Button::Left) {
                    int mx = mousePressed->position.x;
                    int my = mousePressed->position.y;

                    if (mx < 200) {
                        if (guiButtons[0]->onClick(mx, my)) {
                            currentBuildMode = BuildMode::Mine;
                            std::cout << "[GUI] Aktywowano tryb: Budowa Kopalni\n";
                        } 
                        else if (guiButtons[1]->onClick(mx, my)) {
                            currentBuildMode = BuildMode::Factory;
                            std::cout << "[GUI] Aktywowano tryb: Budowa Huty\n";
                        }
                    }
                    else {
                        if (currentBuildMode == BuildMode::Mine) {
                            auto newMine = std::make_unique<Industry::CoalMine>();
                            newMine->setPosition({mx - 20, my - 20});
                            mapObjects.push_back(std::move(newMine));
                            std::cout << "[Mapa] Postawiono Kopalnie\n";
                            currentBuildMode = BuildMode::None;
                        } 
                        else if (currentBuildMode == BuildMode::Factory) {
                            auto newFactory = std::make_unique<Industry::SteelMill>();
                            newFactory->setPosition({mx - 20, my - 20});
                            mapObjects.push_back(std::move(newFactory));
                            std::cout << "[Mapa] Postawiono Hute\n";
                            currentBuildMode = BuildMode::None;
                        }
                    }
                }
            }
        }

        // --- RYSOWANIE KLATKI ---
        window.clear(sf::Color(40, 40, 40));

        // 1. Najpierw rysujemy budynki na mapie
        for (const auto& obj : mapObjects) {
            obj->draw(window);
        }

        // 2. Na wierzchu rysujemy interfejs
        window.draw(sidebarPanel);
        for (const auto& btn : guiButtons) {
            btn->draw(window);
        }

        window.display();
    }


    return 0;
}