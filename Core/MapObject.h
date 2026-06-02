#pragma once
#include "IDrawable.h"
#include "SharedTypes.h"

namespace Core {
    class MapObject : public IDrawable {
    protected:
        Point2D position;
    public:
        virtual ~MapObject() = default;
        void draw() override = 0; 
        virtual void update() = 0;
    };
}