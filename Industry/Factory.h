#pragma once
#include "../Core/MapObject.h"

namespace Industry {
    class Factory : public Core::MapObject {
    private:
        int inputBufferA = 0; 
        int inputBufferB = 0; 

    protected:
        int outputBuffer = 0; // Bufor na wyprodukowane dobra (np. stal)

    public:
        virtual ~Factory() = default;
        
        void draw(sf::RenderWindow& window) override;
        void update() override;
        virtual void processResources() = 0;
        
        void addInputA(int amount);
        void addInputB(int amount);
        void consumeInputA(int amount);
        void consumeInputB(int amount);
        
        int getInputBufferA() const { return inputBufferA; }
        int getInputBufferB() const { return inputBufferB; }

        // Metody wyjściowe
        int getOutputBuffer() const { return outputBuffer; }
        void increaseOutputBuffer(int amount) { if(amount > 0) outputBuffer += amount; }
        void decreaseOutputBuffer(int amount) { if(outputBuffer >= amount) outputBuffer -= amount; }
    };
}