#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "SimulationEngine.h"
#include "Button.h"
#include "InfoPanel.h"
#include "../Logistics/Route.h"

namespace Core {
enum class BuildMode {
    None, CoalMine, IronMine, Factory, PowerPlant, MachineFactory, Route
};

class Application {
private:
    Renderer renderer;
    SimulationEngine engine;
    std::unique_ptr<InfoPanel> infoPanel;

    // Interfejs użytkownika
    sf::RectangleShape sidebarPanel;
    sf::Font font;
    sf::Text statsText;
    std::vector<std::unique_ptr<Button>> guiButtons;

    // Stan interakcji użytkownika
    BuildMode currentBuildMode = BuildMode::None;
    Logistics::Route customRoute;
    int selectedRouteIndex = -1;

    // Wewnętrzne metody pomocnicze
    void setupUI();
    void handleEvents();
    void render();
    void drawTooltips(sf::RenderWindow& window, sf::Vector2i mousePos);

public:
    Application();
    void run();
};
}