#pragma once
#include "../Core/MapObject.h" // Pobieramy baze z folderu Core

namespace Industry {

    class Mine : public Core::MapObject {
    protected:
        int resourceTimer; // Licznik czasu do wygenerowania kolejnej paczki surowca
    public:
        virtual ~Mine() = default;
        
        // Metody nadpisane z MapObject/IDrawable
        void draw() override;
        void update() override;
        
        // Nowa, czysto wirtualna metoda specyficzna dla kopalni
        virtual void generateResource() = 0;
    };

} // namespace Industry