#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "IDrawable.h"

namespace Core {
    /**
     * @class Renderer
     * @brief Warstwa abstrakcji odpowiedzialna za sterowanie oknem biblioteki SFML.
     */
    class Renderer {
    private:
        sf::RenderWindow window; ///< Główne okno aplikacji wideo.
    public:
        /**
         * @brief Tworzy i konfiguruje okno aplikacji (rozdzielczość, limit klatek).
         */
        void initWindow();

        /**
         * @brief Czyści ekran i renderuje wszystkie przekazane do niego obiekty.
         * @param drawables Wektor inteligentnych wskaźników na obiekty implementujące IDrawable.
         */
        void renderAll(const std::vector<std::unique_ptr<IDrawable>>& drawables);

        /**
         * @brief Sprawdza, czy pętla okna systemowego jest nadal aktywna.
         * @return True, jeśli okno jest otwarte i widoczne.
         */
        bool isWindowOpen() const;

        /**
         * @brief Przechwytuje i przetwarza komunikaty z systemu operacyjnego (np. kliknięcie krzyżyka zamykającego okno).
         */
        void handleEvents();

        /**
         * @brief Zapewnia bezpośredni dostęp do okna SFML (np. dla specyficznych komponentów UI).
         * @return Referencja do obiektu sf::RenderWindow.
         */
        sf::RenderWindow& getWindow() { return window; }
    };
}