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
// Dołączamy nagłówki logistyczne dla pełnego łańcucha dostaw
#include "Logistics/MediumTrain.h"
#include "Logistics/Route.h"

enum class BuildMode {
    None,
    Mine,
    Factory
};

int main() {
    std::cout << "==================================================\n";
    std::cout << "   K.O.L.O.S. - Symulacja Lancucha Dostaw \n";
    std::cout << "==================================================\n\n";

    // 1. Inicjalizacja okna graficznego przez Renderer
    Core::Renderer renderer;
    renderer.initWindow();

    sf::RenderWindow& window = renderer.getWindow();

    // Przygotowanie paska bocznego
    sf::RectangleShape sidebarPanel({200.f, 600.f});
    sidebarPanel.setFillColor(sf::Color(60, 60, 60));

    std::vector<std::unique_ptr<Core::Button>> guiButtons;
    std::vector<std::unique_ptr<Core::MapObject>> mapObjects;

    // GUI: Kopalnia (Czerwony), Huta (Niebieski), Uruchom Pociąg (Zielony)
    guiButtons.push_back(std::make_unique<Core::Button>(20, 50, 160, 40, sf::Color(180, 70, 70), "Buduj: Kopalnia"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 110, 160, 40, sf::Color(70, 70, 180), "Buduj: Huta"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 170, 160, 40, sf::Color(70, 180, 70), "Start Pociagu"));

    BuildMode currentBuildMode = BuildMode::None;

    // Wskaźniki pomocnicze do automatycznego bindowania trasy pociągu
    Industry::CoalMine* pointerToMine = nullptr;
    Industry::SteelMill* pointerToFactory = nullptr;

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

                    // Kliknięcie w panel GUI
                    if (mx < 200) {
                        if (guiButtons[0]->onClick(mx, my)) {
                            currentBuildMode = BuildMode::Mine;
                            std::cout << "[GUI] Aktywowano tryb: Budowa Kopalni\n";
                        }
                        else if (guiButtons[1]->onClick(mx, my)) {
                            currentBuildMode = BuildMode::Factory;
                            std::cout << "[GUI] Aktywowano tryb: Budowa Huty\n";
                        }
                        else if (guiButtons[2]->onClick(mx, my)) {
                            // LOGIKA URUCHOMIENIA TRANSPORTU Wahadłowego
                            if (pointerToMine != nullptr && pointerToFactory != nullptr) {
                                Logistics::Route route;
                                // Wyznaczamy trasę od kopalni, do huty i z powrotem do kopalni
                                route.addWaypoint(pointerToMine->getPosition());
                                route.addWaypoint(pointerToFactory->getPosition());
                                route.addWaypoint(pointerToMine->getPosition());

                                auto train = std::make_unique<Logistics::MediumTrain>();
                                train->setRoute(route);
                                // Pociąg startuje na pozycji kopalni
                                train->setPosition(pointerToMine->getPosition());

                                mapObjects.push_back(std::move(train));
                                std::cout << "[Logistyka] Wypuszczono pociag towarowy na trase!\n";
                            } else {
                                std::cout << "[GUI] Blad: Musisz najpierw postawic minimum jedna Kopalnie i jedna Hute!\n";
                            }
                        }
                    }
                    // Kliknięcie w mapę (budowanie)
                    else {
                        if (currentBuildMode == BuildMode::Mine) {
                            auto newMine = std::make_unique<Industry::CoalMine>();
                            newMine->setPosition({mx - 20, my - 20});
                            pointerToMine = newMine.get(); // Zapamiętujemy adres dla pociągu
                            mapObjects.push_back(std::move(newMine));
                            std::cout << "[Mapa] Postawiono Kopalnie\n";
                            currentBuildMode = BuildMode::None;
                        }
                        else if (currentBuildMode == BuildMode::Factory) {
                            auto newFactory = std::make_unique<Industry::SteelMill>();
                            newFactory->setPosition({mx - 20, my - 20});
                            pointerToFactory = newFactory.get(); // Zapamiętujemy adres dla pociągu
                            mapObjects.push_back(std::move(newFactory));
                            std::cout << "[Mapa] Postawiono Hute\n";
                            currentBuildMode = BuildMode::None;
                        }
                    }
                }
            }
        }

        // --- AKTUALIZACJA LOGIKI I SYMULACJA GOSPODARKI ---
        for (const auto& obj : mapObjects) {
            obj->update(); // Ożywiamy timery kopalni i ruch pociągów!
        }

        // Obsługa fizycznego przeładunku cargo na stacjach (żywy łańcuch dostaw)
        if (pointerToMine != nullptr && pointerToFactory != nullptr) {
            for (const auto& obj : mapObjects) {
                // Próbujemy rzutować obiekt na pociąg, aby obsłużyć załadunek/rozładunek
                if (auto* train = dynamic_cast<Logistics::MediumTrain*>(obj.get())) {
                    // Jeśli pociąg jest na pozycji kopalni -> ładuj węgiel
                    if (train->getPosition() == pointerToMine->getPosition()) {
                        train->loadFromMine(*pointerToMine);
                    }
                    // Jeśli pociąg jest na pozycji huty -> rozładuj do bufora
                    if (train->getPosition() == pointerToFactory->getPosition()) {
                        train->unloadToFactory(*pointerToFactory, false);
                    }
                }
            }
        }

        // --- RYSOWANIE KLATKI INTERFEJSU ---
        window.clear(sf::Color(40, 40, 40));

        // 1. Rysujemy budynki oraz poruszające się pociągi
        for (const auto& obj : mapObjects) {
            obj->draw(window);
        }

        // 2. Na wierzchu rysujemy interfejs HUD
        window.draw(sidebarPanel);
        for (const auto& btn : guiButtons) {
            btn->draw(window);
        }

        window.display();
    }

    return 0;
}