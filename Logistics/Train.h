#pragma once
#include "../Core/MapObject.h"
#include "Route.h"

namespace Logistics {

    class Train : public Core::MapObject {
    protected:
        int currentCapacity;
        int maxCapacity;
        float speed;
        
        Route route;
        size_t currentWaypointIndex = 0;

    public:
        virtual ~Train() = default;
        void draw() override;
        void update() override;
        virtual void loadResource(); 
        
        void setRoute(const Route& newRoute);
    };

} // namespace Logistics