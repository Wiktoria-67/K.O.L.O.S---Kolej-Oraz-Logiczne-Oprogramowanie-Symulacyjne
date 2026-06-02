#pragma once
#include "Factory.h"

namespace Industry {

    class MachineFactory : public Factory {
    public:
        MachineFactory();
        void processResources() override;
    };

}