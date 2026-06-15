#pragma once
#include "Mine.h"

namespace Industry {

    /**
     * @class CoalMine
     * @brief Reprezentuje kopalnię węgla o wysokiej przepustowości.
     */
    class CoalMine : public Mine {
    public:
        /**
         * @brief Inicjalizuje obiekt wydobywczy (skrócony cykl produkcyjny: 50 ticków).
         */
        CoalMine();

        /**
         * @brief Odpowiada za bezpośrednie dodanie paczki węgla na stację przeładunkową.
         */
        void generateResource() override;
    };

}