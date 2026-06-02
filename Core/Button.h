#pragma once
#include "UIElement.h"

namespace Core {
    class Button : public UIElement {
    public:
        void draw() override;
        bool onClick(int mouseX, int mouseY) override;
    };
}