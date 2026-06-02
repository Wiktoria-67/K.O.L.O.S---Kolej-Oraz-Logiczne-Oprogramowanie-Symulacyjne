#pragma once

namespace Core {
    class IClickable {
    public:
        virtual ~IClickable() = default;
        virtual bool onClick(int mouseX, int mouseY) = 0;
    };
}