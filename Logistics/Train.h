#pragma once
#include "../Core/MapObject.h"
#include "Route.h"

namespace Industry {
    class Mine;
    class Factory;
}

namespace Logistics {
    class Train : public Core::MapObject {
    protected:
        int currentCapacity; 
        int maxCapacity; 
        float speed; 
        Route route; 
        size_t currentWaypointIndex = 0; 
        Core::ResourceType cargoType = Core::ResourceType::Coal; 

    public:
        virtual ~Train() = default;
        
        void draw(sf::RenderWindow& window) override;
        void update() override;
        virtual void loadResource();
        void setRoute(const Route& newRoute);
        
        void loadFromMine(Industry::Mine& mine);
        void loadFromFactory(Industry::Factory& factory); 
        void unloadToFactory(Industry::Factory& factory, bool toBufferB = false);
        
        void setCargoType(Core::ResourceType type) { cargoType = type; }
        Core::ResourceType getCargoType() const { return cargoType; }
        int getCurrentCapacity() const { return currentCapacity; }

        // NAPRAWIONE: Brak "- 1". Teraz pociąg uczciwie musi dojechać do ostatniego punktu trasy!
        bool isFinished() const { 
            return !route.isEmpty() && currentWaypointIndex >= route.getWaypoints().size(); 
        }
    };
}