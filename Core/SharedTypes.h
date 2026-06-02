#pragma once

namespace Core {
    struct Point2D {
        int x;
        int y;
        
        bool operator==(const Point2D& other) const {
            return x == other.x && y == other.y;
        }
    };

    enum class ResourceType {
        Coal,
        IronOre,
        Steel,
        FinalGoods
    };
}