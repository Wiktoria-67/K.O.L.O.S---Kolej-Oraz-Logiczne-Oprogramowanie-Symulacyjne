#pragma once
#include "../Core/SharedTypes.h"
#include <vector>
#include <initializer_list>

namespace Logistics {

    class Route {
    private:
        std::vector<Core::Point2D> waypoints;
    public:
        Route() = default;
        
        // Konstruktor pozwalający na wygodne tworzenie trasy z listy punktów
        Route(std::initializer_list<Core::Point2D> points) : waypoints(points) {}
        
        void addWaypoint(Core::Point2D point) { waypoints.push_back(point); }
        const std::vector<Core::Point2D>& getWaypoints() const { return waypoints; }
        bool isEmpty() const { return waypoints.empty(); }
    };

} // namespace Logistics