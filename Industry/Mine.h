#pragma once
#include "../Core/MapObject.h"

namespace Industry {

    /**
     * @class Mine
     * @brief Abstrakcyjna klasa bazowa dla budynków wydobywczych (kopalni).
     * * Obiekty dziedziczące po tej klasie generują surowce w oparciu o pętle czasowe.
     */
    class Mine : public Core::MapObject {
    protected:
        int resourceTimer; ///< Licznik czasu (w tickach symulacji) do wygenerowania surowca.
    public:
        virtual ~Mine() = default;
        
        /**
         * @brief Renderuje obiekt kopalni w przestrzeni symulacyjnej.
         * @param window Referencja do okna SFML.
         */
        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Aktualizuje licznik czasu. Po zejściu do zera wywołuje generateResource().
         */
        void update() override;
        
        /**
         * @brief Definiuje sposób i rodzaj dodawanego surowca do bufora wyjściowego kopalni.
         */
        virtual void generateResource() = 0;
    };

}