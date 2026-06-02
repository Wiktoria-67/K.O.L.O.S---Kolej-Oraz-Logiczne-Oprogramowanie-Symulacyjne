#pragma once
#include "../Core/MapObject.h"

namespace Industry {

    class Factory : public Core::MapObject {
    protected:
        int inputBufferA; // Bufor na pierwszy surowiec
        int inputBufferB; // Bufor na ewentualny drugi surowiec
    public:
        virtual ~Factory() = default;

        // Metody nadpisane z MapObject/IDrawable
        void draw(sf::RenderWindow& window) override;
        void update() override;

        // Metoda przetwarzajaca surowce (moze rzucic EmptyStorageException)
        virtual void processResources() = 0; 
    };

}