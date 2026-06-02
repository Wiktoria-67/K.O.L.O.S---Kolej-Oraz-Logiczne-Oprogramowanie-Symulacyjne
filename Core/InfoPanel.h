#pragma once
#include "UIElement.h"

namespace Core {
    class InfoPanel : public UIElement {
    public:
        void draw() override;
        bool onClick(int mouseX, int mouseY) override;
        void updateDisplayData();
    };
}