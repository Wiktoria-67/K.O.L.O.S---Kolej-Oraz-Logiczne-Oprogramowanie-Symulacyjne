#pragma once
#include <SFML/Graphics.hpp>

namespace Core {
    /**
     * @class IDrawable
     * @brief Interfejs dla wszystkich obiektów graficznych w systemie.
     * * Zapewnia polimorfizm dla modułu Renderer, pozwalając na rysowanie
     * obiektów różnego typu przy użyciu jednego wektora.
     */
    class IDrawable {
    public:
        virtual ~IDrawable() = default;

        /**
         * @brief Czysto wirtualna metoda renderująca obiekt.
         * @param window Referencja do aktywnego okna SFML.
         */
        virtual void draw(sf::RenderWindow& window) = 0;
    };
}