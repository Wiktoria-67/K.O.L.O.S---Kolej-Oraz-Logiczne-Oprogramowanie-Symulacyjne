#pragma once
#include "Factory.h"

namespace Industry {

    class PowerPlant : public Factory {
    public:
        PowerPlant();
        void processResources() override;
    };

} // namespace Industry