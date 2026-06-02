#pragma once
#include "IDrawable.h"
#include "IClickable.h"
#include "SharedTypes.h"

namespace Core {
    class UIElement : public IDrawable, public IClickable {
    protected:
        Point2D position;
        int width;
        int height;
    public:
        virtual ~UIElement() = default;
        void draw() override = 0;
        bool onClick(int mouseX, int mouseY) override = 0;
    };
}