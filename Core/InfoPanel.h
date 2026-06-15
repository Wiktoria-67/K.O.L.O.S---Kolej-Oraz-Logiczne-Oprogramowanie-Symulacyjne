#pragma once
#include "UIElement.h"

namespace Core {

    /**
     * @class InfoPanel
     * @brief Panel wyświetlający kluczowe statystyki z przebiegu symulacji.
     * * Z założenia jest to element pasywny (ignorujący kliknięcia).
     */
    class InfoPanel : public UIElement {
    public:
        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Implementacja IClickable, zawsze zwraca false.
         */
        bool onClick(int mouseX, int mouseY) override;

        /**
         * @brief Aktualizuje i odświeża napisy (teksty) wyświetlane na panelu.
         */
        void updateDisplayData();
    };
}