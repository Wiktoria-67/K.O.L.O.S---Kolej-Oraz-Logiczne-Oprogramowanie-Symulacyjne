#pragma once
#include <stdexcept>

namespace Logistics {

    class CapacityExceededException : public std::out_of_range {
    public:
        CapacityExceededException() 
            : std::out_of_range("CapacityExceededException: Brak miejsca w wektorze Inventory.") {}
    };

} // namespace Logistics