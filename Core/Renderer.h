#pragma once
#include <vector>
#include <memory>
#include "IDrawable.h"

namespace Core {
    class Renderer {
    public:
        void initWindow();
        void renderAll(const std::vector<std::unique_ptr<IDrawable>>& drawables);
    };
}