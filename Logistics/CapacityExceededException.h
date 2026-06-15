#pragma once
#include <stdexcept>

namespace Logistics {

    /**
     * @class CapacityExceededException
     * @brief Wyjątek zgłaszany w przypadku próby przeładowania pociągu.
     * * Dziedziczy po std::out_of_range. Gwarantuje bezpieczeństwo mechaniki gry,
     * zapobiegając dodaniu surowca przekraczającego parametr maxCapacity.
     */
    class CapacityExceededException : public std::out_of_range {
    public:
        /**
         * @brief Konstruktor tworzący wyjątek ze standardowym komunikatem o błędzie.
         */
        CapacityExceededException() 
            : std::out_of_range("CapacityExceededException: Brak miejsca w wektorze Inventory.") {}
    };

}