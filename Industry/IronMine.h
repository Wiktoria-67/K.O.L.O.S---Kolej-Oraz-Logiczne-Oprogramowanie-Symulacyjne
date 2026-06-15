#pragma once
#include "Mine.h"

namespace Industry {

    /**
     * @class IronMine
     * @brief Reprezentuje kopalnię rudy żelaza o wydłużonym cyklu pracy.
     */
    class IronMine : public Mine {
    public:
        /**
         * @brief Inicjalizuje ciężki obiekt wydobywczy (dłuższy cykl: 80 ticków).
         */
        IronMine();

        /**
         * @brief Odpowiada za wykopanie ciężkiej rudy i umieszczenie jej w buforze wyjściowym.
         */
        void generateResource() override;
    };

}