#pragma once
#include "../Core/MapObject.h" // Ścieżka relatywna do pliku z modułu Core

namespace Logistics {

    // Przy dziedziczeniu z innego modułu podajemy jego przestrzeń nazw (Core::)
    class Train : public Core::MapObject { 
    protected:
        int currentCapacity;
        int maxCapacity;
        float speed;
    public:
        virtual ~Train() = default;
        void draw() override;
        void update() override;
        virtual void loadResource(); 
    };

}