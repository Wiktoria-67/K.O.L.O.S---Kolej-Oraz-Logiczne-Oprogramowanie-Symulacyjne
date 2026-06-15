#include "Application.h"
#include <iostream>
#include "../Industry/CoalMine.h"
#include "../Industry/IronMine.h"
#include "../Industry/SteelMill.h"
#include "../Industry/PowerPlant.h"
#include "../Industry/MachineFactory.h"
#include "../Logistics/MediumTrain.h"

namespace Core {

Application::Application() : statsText(font) {
    std::cout << "====================================================\n";
    std::cout << "       K.O.L.O.S. - Symulacja Lancucha Dostaw       \n";
    std::cout << "====================================================\n\n";

    renderer.initWindow();
    infoPanel = std::make_unique<InfoPanel>();
    setupUI();
}

void Application::setupUI() {
    sidebarPanel.setSize(sf::Vector2f(200.f, 600.f));
    sidebarPanel.setFillColor(sf::Color(60, 60, 60));

    if (!font.openFromFile("assets/font.ttf")) {
        std::cerr << "[Ostrzezenie] Brak fontu do statystyk!\n";
    }

    statsText.setFont(font);
    statsText.setString("Energia: 0\nPunkty Zwyciestwa: 0");
    statsText.setCharacterSize(16);
    statsText.setFillColor(sf::Color::White);
    statsText.setPosition(sf::Vector2f(20.f, 500.f));

    guiButtons.push_back(std::make_unique<Button>(20, 20, 160, 35, sf::Color(50, 50, 50), "Kop. Wegla"));
    guiButtons.push_back(std::make_unique<Button>(20, 65, 160, 35, sf::Color(160, 82, 45), "Kop. Rudy"));
    guiButtons.push_back(std::make_unique<Button>(20, 110, 160, 35, sf::Color(70, 130, 180), "Huta"));
    guiButtons.push_back(std::make_unique<Button>(20, 155, 160, 35, sf::Color(255, 140, 0), "Elektrownia"));
    guiButtons.push_back(std::make_unique<Button>(20, 200, 160, 35, sf::Color(128, 0, 128), "Fabryka Maszyn"));

    guiButtons.push_back(std::make_unique<Button>(20, 260, 160, 35, sf::Color(180, 180, 70), "Rysuj Trase"));
    guiButtons.push_back(std::make_unique<Button>(20, 305, 160, 35, sf::Color(200, 200, 50), "Wybierz Trase"));
    guiButtons.push_back(std::make_unique<Button>(20, 350, 160, 35, sf::Color(50, 50, 50), "Pociag: Wegiel"));
    guiButtons.push_back(std::make_unique<Button>(20, 395, 160, 35, sf::Color(160, 82, 45), "Pociag: Ruda"));
    guiButtons.push_back(std::make_unique<Button>(20, 440, 160, 35, sf::Color(70, 130, 180), "Pociag: Stal"));
}

void Application::run() {
    while (renderer.getWindow().isOpen()) {
        handleEvents();
        engine.tick();
        render();
    }
}

void Application::handleEvents() {
    sf::RenderWindow& window = renderer.getWindow();
    while (const std::optional event = window.pollEvent()) {
        if (event->is<sf::Event::Closed>()) {
            window.close();
        }

        if (const auto* mousePressed = event->getIf<sf::Event::MouseButtonPressed>()) {
            if (mousePressed->button == sf::Mouse::Button::Left) {
                int mx = mousePressed->position.x;
                int my = mousePressed->position.y;

                if (mx < 200) { // Kliknięcie w panel
                    if (guiButtons[0]->onClick(mx, my)) currentBuildMode = BuildMode::CoalMine;
                    else if (guiButtons[1]->onClick(mx, my)) currentBuildMode = BuildMode::IronMine;
                    else if (guiButtons[2]->onClick(mx, my)) currentBuildMode = BuildMode::Factory;
                    else if (guiButtons[3]->onClick(mx, my)) currentBuildMode = BuildMode::PowerPlant;
                    else if (guiButtons[4]->onClick(mx, my)) currentBuildMode = BuildMode::MachineFactory;

                    else if (guiButtons[5]->onClick(mx, my)) {
                        currentBuildMode = BuildMode::Route;
                        if (!customRoute.isEmpty()) {
                            engine.allRoutes.push_back(customRoute);
                            selectedRouteIndex = static_cast<int>(engine.allRoutes.size() - 1);
                        }
                        customRoute = Logistics::Route();
                    }
                    else if (guiButtons[6]->onClick(mx, my)) {
                        if (!engine.allRoutes.empty()) {
                            selectedRouteIndex = (selectedRouteIndex + 1) % engine.allRoutes.size();
                        }
                    }
                    else if (guiButtons[7]->onClick(mx, my) || guiButtons[8]->onClick(mx, my) || guiButtons[9]->onClick(mx, my)) {
                        if (selectedRouteIndex >= 0 && selectedRouteIndex < engine.allRoutes.size()) {
                            auto train = std::make_unique<Logistics::MediumTrain>();
                            if (guiButtons[7]->onClick(mx, my)) { train->setColor(sf::Color::Cyan); train->setCargoType(Core::ResourceType::Coal); }
                            else if (guiButtons[8]->onClick(mx, my)) { train->setColor(sf::Color::Green); train->setCargoType(Core::ResourceType::IronOre); }
                            else { train->setColor(sf::Color::Magenta); train->setCargoType(Core::ResourceType::Steel); }

                            train->setRoute(engine.allRoutes[selectedRouteIndex]);
                            train->setPosition(engine.allRoutes[selectedRouteIndex].getWaypoints().front());
                            engine.trackNetwork.registerTrain(train.get());
                            engine.mapObjects.push_back(std::move(train));
                        }
                    }
                }
                else { // Kliknięcie w mapę
                    if (currentBuildMode == BuildMode::CoalMine) {
                        auto newMine = std::make_unique<Industry::CoalMine>();
                        newMine->setPosition({mx - 20, my - 20});
                        newMine->setColor(sf::Color(50, 50, 50));
                        engine.pointerToCoalMine = newMine.get();
                        engine.mapObjects.push_back(std::move(newMine));
                        currentBuildMode = BuildMode::None;
                    } else if (currentBuildMode == BuildMode::IronMine) {
                        auto newIronMine = std::make_unique<Industry::IronMine>();
                        newIronMine->setPosition({mx - 20, my - 20});
                        newIronMine->setColor(sf::Color(160, 82, 45));
                        engine.pointerToIronMine = newIronMine.get();
                        engine.mapObjects.push_back(std::move(newIronMine));
                        currentBuildMode = BuildMode::None;
                    } else if (currentBuildMode == BuildMode::Factory) {
                        auto newFactory = std::make_unique<Industry::SteelMill>();
                        newFactory->setPosition({mx - 20, my - 20});
                        newFactory->setColor(sf::Color(70, 130, 180));
                        engine.pointerToFactory = newFactory.get();
                        engine.mapObjects.push_back(std::move(newFactory));
                        currentBuildMode = BuildMode::None;
                    } else if (currentBuildMode == BuildMode::PowerPlant) {
                        auto newPowerPlant = std::make_unique<Industry::PowerPlant>();
                        newPowerPlant->setPosition({mx - 20, my - 20});
                        newPowerPlant->setColor(sf::Color(255, 140, 0));
                        engine.pointerToPowerPlant = newPowerPlant.get();
                        if (engine.pointerToMachineFactory) engine.pointerToMachineFactory->connectToGrid(engine.pointerToPowerPlant);
                        engine.mapObjects.push_back(std::move(newPowerPlant));
                        currentBuildMode = BuildMode::None;
                    } else if (currentBuildMode == BuildMode::MachineFactory) {
                        auto newMachineFactory = std::make_unique<Industry::MachineFactory>();
                        newMachineFactory->setPosition({mx - 20, my - 20});
                        newMachineFactory->setColor(sf::Color(128, 0, 128));
                        engine.pointerToMachineFactory = newMachineFactory.get();
                        if (engine.pointerToPowerPlant) engine.pointerToMachineFactory->connectToGrid(engine.pointerToPowerPlant);
                        engine.mapObjects.push_back(std::move(newMachineFactory));
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
}

void Application::render() {
    sf::RenderWindow& window = renderer.getWindow();
    window.clear(sf::Color(40, 40, 40));

    // Rysowanie budynków i wskaźników
    for (const auto& obj : engine.mapObjects) {
        obj->draw(window);

        if (auto* mine = dynamic_cast<Industry::Mine*>(obj.get())) {
            if (mine->getOutputBuffer() > 0) {
                sf::CircleShape readyIndicator(6.f);
                readyIndicator.setFillColor(sf::Color::Green);
                readyIndicator.setOutlineThickness(1.f);
                readyIndicator.setOutlineColor(sf::Color::White);
                readyIndicator.setPosition(sf::Vector2f(static_cast<float>(mine->getPosition().x + 28), static_cast<float>(mine->getPosition().y - 6)));
                window.draw(readyIndicator);
            }
        }
        else if (auto* factory = dynamic_cast<Industry::Factory*>(obj.get())) {
            if (factory->getOutputBuffer() > 0) {
                sf::CircleShape readyIndicator(6.f);
                readyIndicator.setFillColor(sf::Color::Green);
                readyIndicator.setOutlineThickness(1.f);
                readyIndicator.setOutlineColor(sf::Color::White);
                readyIndicator.setPosition(sf::Vector2f(static_cast<float>(factory->getPosition().x + 28), static_cast<float>(factory->getPosition().y - 6)));
                window.draw(readyIndicator);
            }
        }
    }

    // Rysowanie ustalonych tras
    for (size_t i = 0; i < engine.allRoutes.size(); ++i) {
        if (!engine.allRoutes[i].isEmpty()) {
            const auto& points = engine.allRoutes[i].getWaypoints();
            sf::VertexArray lines(sf::PrimitiveType::LineStrip, points.size());
            for (size_t j = 0; j < points.size(); ++j) {
                lines[j].position = sf::Vector2f(static_cast<float>(points[j].x), static_cast<float>(points[j].y));
                lines[j].color = (i == selectedRouteIndex) ? sf::Color(255, 50, 50) : sf::Color(255, 255, 100);
            }
            window.draw(lines);
        }
    }

    // Rysowanie trasy w trakcie układania
    if (!customRoute.isEmpty()) {
        const auto& points = customRoute.getWaypoints();
        sf::VertexArray lines(sf::PrimitiveType::LineStrip, points.size());
        for (size_t i = 0; i < points.size(); ++i) {
            lines[i].position = sf::Vector2f(static_cast<float>(points[i].x), static_cast<float>(points[i].y));
            lines[i].color = sf::Color(255, 150, 50);
        }
        window.draw(lines);
    }

    // GUI boczne
    window.draw(sidebarPanel);
    for (const auto& btn : guiButtons) {
        btn->draw(window);
    }

    // Aktualizacja statystyk tekstowych z silnika
    int currentEnergy = engine.pointerToPowerPlant ? engine.pointerToPowerPlant->getGeneratedEnergy() : 0;
    int currentVP = engine.pointerToMachineFactory ? engine.pointerToMachineFactory->getVictoryPoints() : 0;
    statsText.setString("Energia: " + std::to_string(currentEnergy) + "\nPunkty Zwyciestwa: " + std::to_string(currentVP));
    window.draw(statsText);

    // Tooltipy (Hover)
    drawTooltips(window, sf::Mouse::getPosition(window));

    window.display();
}

void Application::drawTooltips(sf::RenderWindow& window, sf::Vector2i mousePos) {
    std::string hoverText = "";

    for (const auto& obj : engine.mapObjects) {
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
}

}