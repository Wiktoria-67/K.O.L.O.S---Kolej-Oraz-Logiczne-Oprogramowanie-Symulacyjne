#pragma once

/**
 * @namespace Core
 * @brief Główny moduł systemu, zawierający silnik symulacji, system renderowania i interfejsy bazowe.
 */
namespace Core {

    /**
     * @struct Point2D
     * @brief Struktura reprezentująca współrzędne dwuwymiarowe w przestrzeni symulacji.
     */
    struct Point2D {
        int x; ///< Współrzędna pozioma X.
        int y; ///< Współrzędna pionowa Y.
        
        /**
         * @brief Przeciążony operator porównania.
         * @param other Inny punkt do porównania.
         * @return True, jeśli oba punkty mają identyczne współrzędne X i Y.
         */
        bool operator==(const Point2D& other) const {
            return x == other.x && y == other.y;
        }
    };

    /**
     * @enum ResourceType
     * @brief Typy surowców obsługiwane przez system logistyki i przemysłu.
     */
    enum class ResourceType {
        Coal, ///< Węgiel - paliwo dla elektrowni i hut.
        IronOre, ///< Ruda żelaza - surowiec przetapiany w hutach.
        Steel, ///< Stal - produkt huty, wykorzystywany do budowy maszyn.
        FinalGoods ///< Dobra finalne - końcowy produkt łańcucha logistycznego.
    };
}