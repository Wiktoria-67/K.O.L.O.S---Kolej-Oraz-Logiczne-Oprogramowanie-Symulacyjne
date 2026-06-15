#include <iostream>
#include <vector>
#include <memory>
#include <optional>
#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>

// Nagłówki z Twojego projektu
#include "Core/Renderer.h"
#include "Core/Button.h"
#include "Core/IDrawable.h"
#include "Core/MapObject.h"
#include "Core/InfoPanel.h"
#include "Industry/Mine.h"
#include "Industry/Factory.h" // Dodane dla wskaźników Huty
#include "Industry/CoalMine.h"
#include "Industry/IronMine.h"
#include "Industry/SteelMill.h"
#include "Industry/PowerPlant.h"
#include "Industry/MachineFactory.h"
#include "Logistics/SmallTrain.h"
#include "Logistics/MediumTrain.h"
#include "Logistics/LargeTrain.h"
#include "Logistics/Route.h"
#include "Logistics/TrackNetwork.h"
#include "Logistics/CollisionException.h"

enum class BuildMode {
    None,
    CoalMine,
    IronMine,
    Factory,
    PowerPlant,
    MachineFactory,
    Route
};

int main() {
    std::cout << "====================================================\n";
    std::cout << "       K.O.L.O.S. - Symulacja Lancucha Dostaw       \n";
    std::cout << "====================================================\n\n";

    Core::Renderer renderer;
    renderer.initWindow();
    sf::RenderWindow& window = renderer.getWindow();

    sf::RectangleShape sidebarPanel({200.f, 600.f});
    sidebarPanel.setFillColor(sf::Color(60, 60, 60));

    sf::Font font;
    if (!font.openFromFile("assets/font.ttf")) {
        std::cerr << "[Ostrzezenie] Brak fontu do statystyk!\n";
    }
    sf::Text statsText(font, "Energia: 0\nPunkty Zwyciestwa: 0", 16);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition({20.f, 500.f});

    std::vector<std::unique_ptr<Core::Button>> guiButtons;
    std::vector<std::unique_ptr<Core::MapObject>> mapObjects;

    Logistics::TrackNetwork trackNetwork;
    auto infoPanel = std::make_unique<Core::InfoPanel>();

    // Budynki
    guiButtons.push_back(std::make_unique<Core::Button>(20, 20, 160, 35, sf::Color(50, 50, 50), "Kop. Wegla"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 65, 160, 35, sf::Color(160, 82, 45), "Kop. Rudy"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 110, 160, 35, sf::Color(70, 130, 180), "Huta"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 155, 160, 35, sf::Color(255, 140, 0), "Elektrownia"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 200, 160, 35, sf::Color(128, 0, 128), "Fabryka Maszyn"));

    // Logistyka i Trasy
    guiButtons.push_back(std::make_unique<Core::Button>(20, 260, 160, 35, sf::Color(180, 180, 70), "Rysuj Trase"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 305, 160, 35, sf::Color(200, 200, 50), "Wybierz Trase"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 350, 160, 35, sf::Color(50, 50, 50), "Pociag: Wegiel"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 395, 160, 35, sf::Color(160, 82, 45), "Pociag: Ruda"));
    guiButtons.push_back(std::make_unique<Core::Button>(20, 440, 160, 35, sf::Color(70, 130, 180), "Pociag: Stal"));

    BuildMode currentBuildMode = BuildMode::None;

    Logistics::Route customRoute;
    std::vector<Logistics::Route> allRoutes;
    int selectedRouteIndex = -1;

    Industry::CoalMine* pointerToCoalMine = nullptr;
    Industry::IronMine* pointerToIronMine = nullptr;
    Industry::SteelMill* pointerToFactory = nullptr;
    Industry::PowerPlant* pointerToPowerPlant = nullptr;
    Industry::MachineFactory* pointerToMachineFactory = nullptr;

    long long tickCounter = 0;

    try {
        while (window.isOpen()) {
            while (const std::optional event = window.pollEvent()) {
                if (event->is<sf::Event::Closed>()) {
                    window.close();
                }

                if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
                    if (mousePressed->button == sf::Mouse::Button::Left) {
                        int mx = mousePressed->position.x;
                        int my = mousePressed->position.y;

                        if (mx < 200) {
                            if (guiButtons[0]->onClick(mx, my)) currentBuildMode = BuildMode::CoalMine;
                            else if (guiButtons[1]->onClick(mx, my)) currentBuildMode = BuildMode::IronMine;
                            else if (guiButtons[2]->onClick(mx, my)) currentBuildMode = BuildMode::Factory;
                            else if (guiButtons[3]->onClick(mx, my)) currentBuildMode = BuildMode::PowerPlant;
                            else if (guiButtons[4]->onClick(mx, my)) currentBuildMode = BuildMode::MachineFactory;

                            else if (guiButtons[5]->onClick(mx, my)) {
                                currentBuildMode = BuildMode::Route;
                                if (!customRoute.isEmpty()) {
                                    allRoutes.push_back(customRoute);
                                    selectedRouteIndex = static_cast<int>(allRoutes.size() - 1); // Zabezpieczenie size_t -> int
                                }
                                customRoute = Logistics::Route();
                            }
                            else if (guiButtons[6]->onClick(mx, my)) {
                                if (!allRoutes.empty()) {
                                    selectedRouteIndex = (selectedRouteIndex + 1) % allRoutes.size();
                                }
                            }
                            else if (guiButtons[7]->onClick(mx, my)) {
                                if (selectedRouteIndex >= 0 && selectedRouteIndex < allRoutes.size()) {
                                    auto train = std::make_unique<Logistics::MediumTrain>();
                                    train->setColor(sf::Color::Cyan);
                                    train->setCargoType(Core::ResourceType::Coal);
                                    train->setRoute(allRoutes[selectedRouteIndex]);
                                    train->setPosition(allRoutes[selectedRouteIndex].getWaypoints().front());
                                    trackNetwork.registerTrain(train.get());
                                    mapObjects.push_back(std::move(train));
                                }
                            }
                            else if (guiButtons[8]->onClick(mx, my)) {
                                if (selectedRouteIndex >= 0 && selectedRouteIndex < allRoutes.size()) {
                                    auto train = std::make_unique<Logistics::MediumTrain>();
                                    train->setColor(sf::Color::Green);
                                    train->setCargoType(Core::ResourceType::IronOre);
                                    train->setRoute(allRoutes[selectedRouteIndex]);
                                    train->setPosition(allRoutes[selectedRouteIndex].getWaypoints().front());
                                    trackNetwork.registerTrain(train.get());
                                    mapObjects.push_back(std::move(train));
                                }
                            }
                            else if (guiButtons[9]->onClick(mx, my)) {
                                if (selectedRouteIndex >= 0 && selectedRouteIndex < allRoutes.size()) {
                                    auto train = std::make_unique<Logistics::MediumTrain>();
                                    train->setColor(sf::Color::Magenta);
                                    train->setCargoType(Core::ResourceType::Steel);
                                    train->setRoute(allRoutes[selectedRouteIndex]);
                                    train->setPosition(allRoutes[selectedRouteIndex].getWaypoints().front());
                                    trackNetwork.registerTrain(train.get());
                                    mapObjects.push_back(std::move(train));
                                }
                            }
                        }
                        else {
                            if (currentBuildMode == BuildMode::CoalMine) {
                                auto newMine = std::make_unique<Industry::CoalMine>();
                                newMine->setPosition({mx - 20, my - 20});
                                newMine->setColor(sf::Color(50, 50, 50));
                                pointerToCoalMine = newMine.get();
                                mapObjects.push_back(std::move(newMine));
                                currentBuildMode = BuildMode::None;
                            } else if (currentBuildMode == BuildMode::IronMine) {
                                auto newIronMine = std::make_unique<Industry::IronMine>();
                                newIronMine->setPosition({mx - 20, my - 20});
                                newIronMine->setColor(sf::Color(160, 82, 45));
                                pointerToIronMine = newIronMine.get();
                                mapObjects.push_back(std::move(newIronMine));
                                currentBuildMode = BuildMode::None;
                            } else if (currentBuildMode == BuildMode::Factory) {
                                auto newFactory = std::make_unique<Industry::SteelMill>();
                                newFactory->setPosition({mx - 20, my - 20});
                                newFactory->setColor(sf::Color(70, 130, 180));
                                pointerToFactory = newFactory.get();
                                mapObjects.push_back(std::move(newFactory));
                                currentBuildMode = BuildMode::None;
                            } else if (currentBuildMode == BuildMode::PowerPlant) {
                                auto newPowerPlant = std::make_unique<Industry::PowerPlant>();
                                newPowerPlant->setPosition({mx - 20, my - 20});
                                newPowerPlant->setColor(sf::Color(255, 140, 0));
                                pointerToPowerPlant = newPowerPlant.get();
                                if (pointerToMachineFactory) pointerToMachineFactory->connectToGrid(pointerToPowerPlant);
                                mapObjects.push_back(std::move(newPowerPlant));
                                currentBuildMode = BuildMode::None;
                            } else if (currentBuildMode == BuildMode::MachineFactory) {
                                auto newMachineFactory = std::make_unique<Industry::MachineFactory>();
                                newMachineFactory->setPosition({mx - 20, my - 20});
                                newMachineFactory->setColor(sf::Color(128, 0, 128));
                                pointerToMachineFactory = newMachineFactory.get();
                                if (pointerToPowerPlant) pointerToMachineFactory->connectToGrid(pointerToPowerPlant);
                                mapObjects.push_back(std::move(newMachineFactory));
                                currentBuildMode = BuildMode::None;
                            } else if (currentBuildMode == BuildMode::Route) {
                                if (customRoute.getWaypoints().empty()) {
                                    customRoute.addWaypoint({mx, my});
                                } else {
                                    auto lastPoint = customRoute.getWaypoints().back();
                                    int dx = std::abs(mx - lastPoint.x);
                                    int dy = std::abs(my - lastPoint.y);
                                    Core::Point2D newPoint;
                                    if (dx > dy) newPoint = {mx, lastPoint.y};
                                    else newPoint = {lastPoint.x, my};
                                    customRoute.addWaypoint(newPoint);
                                }
                            }
                        }
                    }
                }
            }

            tickCounter++;

            try {
                trackNetwork.checkCollisions();
            } catch (const Logistics::CollisionException& e) {

            }

            for (const auto& obj : mapObjects) {
                if (dynamic_cast<Industry::IronMine*>(obj.get()) && tickCounter % 2 == 0) {
                    continue;
                }
                obj->update();
            }

            for (const auto& obj : mapObjects) {
                if (auto* train = dynamic_cast<Logistics::Train*>(obj.get())) {
                    auto cargo = train->getCargoType();

                    for (const auto& targetObj : mapObjects) {
                        if (cargo == Core::ResourceType::Coal) {
                            if (auto* mine = dynamic_cast<Industry::CoalMine*>(targetObj.get())) train->loadFromMine(*mine);
                            if (auto* mill = dynamic_cast<Industry::SteelMill*>(targetObj.get())) train->unloadToFactory(*mill, false);
                            if (auto* plant = dynamic_cast<Industry::PowerPlant*>(targetObj.get())) train->unloadToFactory(*plant, false);
                        }
                        else if (cargo == Core::ResourceType::IronOre) {
                            if (auto* mine = dynamic_cast<Industry::IronMine*>(targetObj.get())) train->loadFromMine(*mine);
                            if (auto* mill = dynamic_cast<Industry::SteelMill*>(targetObj.get())) train->unloadToFactory(*mill, true);
                        }
                        else if (cargo == Core::ResourceType::Steel) {
                            if (auto* mill = dynamic_cast<Industry::SteelMill*>(targetObj.get())) train->loadFromFactory(*mill);
                            if (auto* mFact = dynamic_cast<Industry::MachineFactory*>(targetObj.get())) train->unloadToFactory(*mFact, false);
                        }
                    }
                }
            }

            //--- RYSOWANIE KLATKI INTERFEJSU ---
            window.clear(sf::Color(40, 40, 40));

            for (const auto& obj : mapObjects) {
                obj->draw(window);

                // Zielona kropka dla Kopalni
                if (auto* mine = dynamic_cast<Industry::Mine*>(obj.get())) {
                    if (mine->getOutputBuffer() > 0) {
                        sf::CircleShape readyIndicator(6.f);
                        readyIndicator.setFillColor(sf::Color::Green);
                        readyIndicator.setOutlineThickness(1.f);
                        readyIndicator.setOutlineColor(sf::Color::White);
                        readyIndicator.setPosition({static_cast<float>(mine->getPosition().x + 28), static_cast<float>(mine->getPosition().y - 6)});
                        window.draw(readyIndicator);
                    }
                }
                // Zielona kropka dla Huty
                else if (auto* factory = dynamic_cast<Industry::Factory*>(obj.get())) {
                    if (factory->getOutputBuffer() > 0) {
                        sf::CircleShape readyIndicator(6.f);
                        readyIndicator.setFillColor(sf::Color::Green);
                        readyIndicator.setOutlineThickness(1.f);
                        readyIndicator.setOutlineColor(sf::Color::White);
                        readyIndicator.setPosition({static_cast<float>(factory->getPosition().x + 28), static_cast<float>(factory->getPosition().y - 6)});
                        window.draw(readyIndicator);
                    }
                }
            }

            for (size_t i = 0; i < allRoutes.size(); ++i) {
                if (!allRoutes[i].isEmpty()) {
                    const auto& points = allRoutes[i].getWaypoints();
                    sf::VertexArray lines(sf::PrimitiveType::LineStrip, points.size());
                    for (size_t j = 0; j < points.size(); ++j) {
                        lines[j].position = sf::Vector2f(static_cast<float>(points[j].x), static_cast<float>(points[j].y));
                        lines[j].color = (i == selectedRouteIndex) ? sf::Color(255, 50, 50) : sf::Color(255, 255, 100);
                    }
                    window.draw(lines);
                }
            }

            if (!customRoute.isEmpty()) {
                const auto& points = customRoute.getWaypoints();
                sf::VertexArray lines(sf::PrimitiveType::LineStrip, points.size());
                for (size_t i = 0; i < points.size(); ++i) {
                    lines[i].position = sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y));
                    lines[i].color = sf::Color(255, 150, 50);
                }
                window.draw(lines);
            }

            window.draw(sidebarPanel);
            for (const auto& btn : guiButtons) {
                btn->draw(window);
            }

            int currentEnergy = pointerToPowerPlant ? pointerToPowerPlant->getGeneratedEnergy() : 0;
            int currentVP = pointerToMachineFactory ? pointerToMachineFactory->getVictoryPoints() : 0;

            statsText.setString("Energia: " + std::to_string(currentEnergy) +
                                "\nPunkty Zwyciestwa: " + std::to_string(currentVP));
            window.draw(statsText);

            //wyswietlanie informacji po najechaniu na element
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            std::string hoverText = "";

            for (const auto& obj : mapObjects) {
                int objX = obj->getPosition().x;
                int objY = obj->getPosition().y;
                int size = (dynamic_cast<Logistics::Train*>(obj.get())) ? 20 : 40;

                if (mousePos.x >= objX && mousePos.x <= objX + size &&
                    mousePos.y >= objY && mousePos.y <= objY + size) {

                    if (auto* coalMine = dynamic_cast<Industry::CoalMine*>(obj.get())) {
                        hoverText = "Kopalnia Wegla\nMagazyn: " + std::to_string(coalMine->getOutputBuffer());
                    } else if (auto* ironMine = dynamic_cast<Industry::IronMine*>(obj.get())) {
                        hoverText = "Kopalnia Rudy\nMagazyn: " + std::to_string(ironMine->getOutputBuffer());
                    } else if (auto* steelMill = dynamic_cast<Industry::SteelMill*>(obj.get())) {
                        hoverText = "Huta Stali\nWegiel: " + std::to_string(steelMill->getInputBufferA()) +
                                    "\nRuda: " + std::to_string(steelMill->getInputBufferB()) +
                                    "\nGotowa Stal: " + std::to_string(steelMill->getOutputBuffer());
                    } else if (auto* powerPlant = dynamic_cast<Industry::PowerPlant*>(obj.get())) {
                        hoverText = "Elektrownia\nWegiel: " + std::to_string(powerPlant->getInputBufferA()) +
                                    "\nSiec (Energia): " + std::to_string(powerPlant->getGeneratedEnergy());
                    } else if (auto* machineFactory = dynamic_cast<Industry::MachineFactory*>(obj.get())) {
                        hoverText = "Fabryka Maszyn\nStal: " + std::to_string(machineFactory->getInputBufferA()) +
                                    "\nWyprodukowano: " + std::to_string(machineFactory->getVictoryPoints() / 50) + " maszyn";
                    } else if (auto* train = dynamic_cast<Logistics::Train*>(obj.get())) {
                        std::string cargoName = (train->getCargoType() == Core::ResourceType::Coal) ? "Wegiel" :
                                                    (train->getCargoType() == Core::ResourceType::IronOre) ? "Ruda" : "Stal";
                        hoverText = "Pociag Towarowy\nLadunek: " + cargoName +
                                    "\nZajete miejsce: " + std::to_string(train->getCurrentCapacity());
                    }
                    break;
                }
            }

            if (!hoverText.empty()) {
                sf::Text tooltipText(font, hoverText, 14);
                tooltipText.setFillColor(sf::Color::White);
                tooltipText.setPosition(sf::Vector2f(static_cast<float>(mousePos.x + 15), static_cast<float>(mousePos.y + 15)));

                sf::FloatRect textBounds = tooltipText.getGlobalBounds();
                sf::RectangleShape tooltipBg(sf::Vector2f(textBounds.size.x + 10.f, textBounds.size.y + 10.f));
                tooltipBg.setFillColor(sf::Color(20, 20, 20, 230));
                tooltipBg.setOutlineThickness(1.f);
                tooltipBg.setOutlineColor(sf::Color(100, 100, 100));
                tooltipBg.setPosition(sf::Vector2f(static_cast<float>(mousePos.x + 10), static_cast<float>(mousePos.y + 10)));

                window.draw(tooltipBg);
                window.draw(tooltipText);
            }


            window.display();
        }
    } catch (const std::exception& e) {
        std::cerr << "\n[BLAD KRYTYCZNY] Program zakonczony awaryjnie: " << e.what() << "\n";
        return -1;
    }

    return 0;
}