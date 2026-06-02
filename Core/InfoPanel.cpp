#include "InfoPanel.h"
#include <iostream>

namespace Core {

    void InfoPanel::draw(sf::RenderWindow& window) {
        std::cout << "[InfoPanel] Rysowanie panelu informacyjnego.\n";
    }

    bool InfoPanel::onClick(int mouseX, int mouseY) {
        return false;
    }

    void InfoPanel::updateDisplayData() {
        std::cout << "[InfoPanel] Zaktualizowano statystyki wyswietlania.\n";
    }

}