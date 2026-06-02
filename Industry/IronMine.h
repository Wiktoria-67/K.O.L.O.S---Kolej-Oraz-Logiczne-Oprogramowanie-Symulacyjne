#pragma once
#include "Mine.h"

namespace Industry {

    class IronMine : public Mine {
    public:
        IronMine();
        void generateResource() override;
    };

}