#pragma once
#include "../Core/MapObject.h" // Pobieramy baze z folderu Core

namespace Industry {

    class Mine : public Core::MapObject {
    protected:
        int resourceTimer; // Licznik czasu do wygenerowania kolejnej paczki surowca
    public:
        virtual ~Mine() = default;
        
        void draw(sf::RenderWindow& window) override;
        void update() override;
        
        virtual void generateResource() = 0;
    };

}