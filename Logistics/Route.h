#pragma once
#include "../Core/SharedTypes.h"
#include <vector>
#include <initializer_list>

/**
 * @namespace Logistics
 * @brief Moduł odpowiedzialny za transport, trasy i zarządzanie surowcami w ruchu.
 */
namespace Logistics {

    /**
     * @class Route
     * @brief Reprezentuje trasę przejazdu składającą się z serii punktów kontrolnych.
     * * Trasa przechowuje listę współrzędnych przestrzennych (węzłów),
     * po których obiekty mobilne poruszają się w symulacji.
     */
    class Route {
    private:
        std::vector<Core::Point2D> waypoints; ///< Wektor przechowujący kolejne punkty trasy.
    public:
        /**
         * @brief Konstruktor domyślny. Tworzy pustą trasę.
         */
        Route() = default;
        
        /**
         * @brief Konstruktor inicjalizujący trasę z gotowej listy punktów.
         * @param points Lista inicjalizacyjna współrzędnych 2D.
         */
        Route(std::initializer_list<Core::Point2D> points) : waypoints(points) {}
        
        /**
         * @brief Dodaje nowy punkt kontrolny na koniec trasy.
         * @param point Współrzędne nowego węzła.
         */
        void addWaypoint(Core::Point2D point) { waypoints.push_back(point); }

        /**
         * @brief Zwraca stałą referencję do wszystkich punktów na trasie.
         * @return Wektor punktów typu Core::Point2D.
         */
        const std::vector<Core::Point2D>& getWaypoints() const { return waypoints; }

        /**
         * @brief Sprawdza, czy trasa nie zawiera żadnych punktów.
         * @return True, jeśli trasa jest pusta, w przeciwnym razie false.
         */
        bool isEmpty() const { return waypoints.empty(); }
    };

}