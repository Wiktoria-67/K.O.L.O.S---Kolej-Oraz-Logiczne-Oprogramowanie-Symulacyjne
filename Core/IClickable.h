#pragma once

namespace Core {
    /**
     * @class IClickable
     * @brief Interfejs dla elementów reagujących na interakcje użytkownika.
     */
    class IClickable {
    public:
        virtual ~IClickable() = default;

        /**
         * @brief Sprawdza, czy obiekt został kliknięty na podstawie współrzędnych myszy.
         * @param mouseX Współrzędna X kursora.
         * @param mouseY Współrzędna Y kursora.
         * @return True, jeśli punkt uderzenia zawiera się w obrysie obiektu (tzw. hitboxie).
         */
        virtual bool onClick(int mouseX, int mouseY) = 0;
    };
}