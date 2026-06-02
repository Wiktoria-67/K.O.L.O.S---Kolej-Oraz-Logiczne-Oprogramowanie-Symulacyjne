#pragma once
#include "IDrawable.h"
#include "SharedTypes.h"

namespace Core {
    class MapObject : public IDrawable {
    protected:
        Point2D position;
    public:
        virtual ~MapObject() = default;
        void draw(sf::RenderWindow& window) override = 0;
        virtual void update() = 0;

        void setPosition(Point2D pos) { position = pos; }
        Point2D getPosition() const { return position; }
    };
}