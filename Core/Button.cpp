#include "Button.h"
#include <iostream>

namespace Core {

    void Button::draw() {
        std::cout << "[Button] Rysowanie przycisku w oknie.\n";
    }

    bool Button::onClick(int mouseX, int mouseY) {
        std::cout << "[Button] Zarejestrowano klikniecie na wspolrzednych X:" 
                  << mouseX << " Y:" << mouseY << "\n";
        return true;
    }

} // namespace Core