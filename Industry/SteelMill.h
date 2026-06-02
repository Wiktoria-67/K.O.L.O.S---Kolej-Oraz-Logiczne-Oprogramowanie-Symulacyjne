#pragma once
#include "Factory.h"

namespace Industry {

    class SteelMill : public Factory {
    public:
        SteelMill();
        void processResources() override;
    };

} // namespace Industry