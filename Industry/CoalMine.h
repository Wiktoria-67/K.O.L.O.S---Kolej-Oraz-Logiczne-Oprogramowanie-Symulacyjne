#pragma once
#include "Mine.h"

namespace Industry {

    class CoalMine : public Mine {
    public:
        CoalMine();
        void generateResource() override;
    };

} // namespace Industry