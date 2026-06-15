#pragma once
#include "IDrawable.h"
#include "SharedTypes.h"

namespace Core {

    /**
     * @class MapObject
     * @brief Abstrakcyjna klasa bazowa dla fizycznych elementów na mapie symulacji.
     * * Dziedziczą po niej m.in. pociągi (Logistics) i fabryki (Industry).
     */
    class MapObject : public IDrawable {
    protected:
        Point2D position; ///< Aktualna pozycja obiektu na mapie.
    public:
        virtual ~MapObject() = default;
        void draw(sf::RenderWindow& window) override = 0;

        /**
         * @brief Czysto wirtualna metoda odświeżająca stan logiczny obiektu.
         * * Wywoływana automatycznie w każdym "ticku" silnika.
         */
        virtual void update() = 0;

        /**
         * @brief Ustawia nową pozycję obiektu.
         * @param pos Nowe współrzędne 2D.
         */
        void setPosition(Point2D pos) { position = pos; }

        /**
         * @brief Pobiera aktualną pozycję obiektu.
         * @return Aktualne współrzędne w formacie Point2D.
         */
        Point2D getPosition() const { return position; }
    };
}