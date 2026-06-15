#pragma once
#include "Factory.h"

namespace Industry {

    /**
     * @class SteelMill
     * @brief Reprezentuje ciężką hutę z podwójną linią zaopatrzeniową.
     * * Jako jedyna fabryka bezwzględnie wymaga dostaw z dwóch różnych typów kopalń.
     */
    class SteelMill : public Factory {
    public:
        /**
         * @brief Inicjalizuje hutę żelaza (korzysta z inputBufferA i inputBufferB).
         */
        SteelMill();

        /**
         * @brief Przepala węgiel i rudę żelaza, tworząc gotową stal do transportu.
         * @throw EmptyStorageException Jeśli brakuje któregokolwiek z dwóch wymaganych surowców.
         */
        void processResources() override;
    };

}