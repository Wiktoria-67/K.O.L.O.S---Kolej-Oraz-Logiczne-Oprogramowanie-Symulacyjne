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
#include "Logistics/MediumTrain.h"
#include "Logistics/Route.h"
#include <cmath>

enum class BuildMode {
    None,
    Mine,
    Factory,
    Route
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
    guiButtons.push_back(std::make_unique<Core::Button>(20, 170, 160, 40, sf::Color(180, 180, 70), "Rysuj Trase"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 230, 160, 40, sf::Color(70, 180, 70), "Start Pociagu"));

    BuildMode currentBuildMode = BuildMode::None;

    // Obiekt do tymczasowego magazynowania punktów klikniętych przez gracza
    Logistics::Route customRoute;

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
                            currentBuildMode = BuildMode::Route;
                            customRoute = Logistics::Route(); // Czyszczenie poprzedniej trasy przed nowym rysowaniem
                            std::cout << "[GUI] Aktywowano tryb: Rysowanie Trasy. Klikaj na mapie, aby dodawac wezly.\n";
                        }
                        else if (guiButtons[3]->onClick(mx, my)) {
                            // Uruchomienie pociągu na wyznaczonej trasie
                            if (customRoute.getWaypoints().size() >= 2) {
                                auto train = std::make_unique<Logistics::MediumTrain>();
                                train->setRoute(customRoute);

                                // Pociąg zaczyna fizycznie na pierwszym postawionym węźle trasy
                                train->setPosition(customRoute.getWaypoints().front());

                                mapObjects.push_back(std::move(train));
                                std::cout << "[Logistyka] Wypuszczono pociag na narysowana trase!\n";
                                currentBuildMode = BuildMode::None;
                            } else {
                                std::cout << "[GUI] Blad: Trasa musi miec minimum 2 punkty, aby pociag ruszyl!\n";
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
                            //std::cout << "[Debug] Huta postawiona na: " << pointerToFactory->getPosition().x << "\n";
                            mapObjects.push_back(std::move(newFactory));
                            std::cout << "[Mapa] Postawiono Hute\n";
                            currentBuildMode = BuildMode::None;
                        }
                        else if (currentBuildMode == BuildMode::Route) {
                            if (customRoute.getWaypoints().empty()) {
                                // Pierwszy punkt trasy zawsze stawiamy swobodnie
                                customRoute.addWaypoint({mx, my});
                                std::cout << "[Trasa] Dodano pierwszy wezel: (" << mx << ", " << my << ")\n";
                            } else {
                                // Pobieramy ostatni postawiony punkt, by się do niego wyrównać
                                auto lastPoint = customRoute.getWaypoints().back();

                                // Liczymy różnicę w osi X i Y
                                int dx = std::abs(mx - lastPoint.x);
                                int dy = std::abs(my - lastPoint.y);

                                Core::Point2D newPoint;

                                // Sprawdzamy, w którym kierunku ruch myszki był większy
                                if (dx > dy) {
                                    // Ruch poziomy: zachowujemy nowe X, ale blokujemy stare Y
                                    newPoint = {mx, lastPoint.y};
                                } else {
                                    // Ruch pionowy: zachowujemy nowe Y, ale blokujemy stare X
                                    newPoint = {lastPoint.x, my};
                                }

                                customRoute.addWaypoint(newPoint);
                                std::cout << "[Trasa] Dodano wezel 90-stopni: (" << newPoint.x << ", " << newPoint.y << ")\n";
                            }
                        }
                    }
                }
            }
        }

        // --- AKTUALIZACJA LOGIKI I SYMULACJA GOSPODARKI ---
        for (const auto& obj : mapObjects) {
            obj->update(); // Ożywiamy timery kopalni i ruch pociągów!
        }

        // Obsługa fizycznego przeładunku cargo na stacjach
        if (pointerToMine != nullptr && pointerToFactory != nullptr) {
            for (const auto& obj : mapObjects) {
                if (auto* train = dynamic_cast<Logistics::MediumTrain*>(obj.get())) {

                    // Pociąg sam sprawdza odległość (hitbox) wewnątrz tych metod.
                    // Jeśli jest daleko - metody po prostu nic nie zrobią.
                    train->loadFromMine(*pointerToMine);
                    train->unloadToFactory(*pointerToFactory, false);

                }
            }
        }

        // --- RYSOWANIE KLATKI INTERFEJSU ---
        window.clear(sf::Color(40, 40, 40));

        // 1. Rysujemy budynki oraz poruszające się pociągi
        for (const auto& obj : mapObjects) {
            obj->draw(window);
        }

        // 2. Rysowanie projektowanej linii torów (Wizualizacja VertexArray w SFML 3)
        if (!customRoute.isEmpty()) {
            const auto& points = customRoute.getWaypoints();
            sf::VertexArray lines(sf::PrimitiveType::LineStrip, points.size());

            for (size_t i = 0; i < points.size(); ++i) {
                lines[i].position = sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y));
                lines[i].color = sf::Color(255, 255, 100); // Żółty kolor wizualizacji linii kolejowej
            }
            window.draw(lines);
        }

        // 3. Na wierzchu rysujemy interfejs HUD,
        window.draw(sidebarPanel);
        for (const auto& btn : guiButtons) {
            btn->draw(window);
        }

        window.display();
    }

    return 0;
}