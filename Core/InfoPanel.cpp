#include "InfoPanel.h"
#include <iostream>

namespace Core {

    void InfoPanel::draw() {
        std::cout << "[InfoPanel] Rysowanie panelu informacyjnego.\n";
    }

    bool InfoPanel::onClick(int mouseX, int mouseY) {
        return false; // Panel zazwyczaj nie jest klikalny w ten sam sposob co przycisk
    }

    void InfoPanel::updateDisplayData() {
        std::cout << "[InfoPanel] Zaktualizowano statystyki wyswietlania.\n";
    }

} // namespace Core