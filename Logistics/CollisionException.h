#pragma once
#include <stdexcept>
#include <string>

namespace Logistics {

    /**
     * @class CollisionException
     * @brief Wyjątek zgłaszany w przypadku zderzenia obiektów mobilnych.
     * * Dziedziczy po std::runtime_error. Wykorzystywany przez TrackNetwork
     * do przerwania symulacji w wypadku naruszenia fizyki gry.
     */
    class CollisionException : public std::runtime_error {
    public:
        /**
         * @brief Konstruktor domyślny z generycznym komunikatem błędu kolizji.
         */
        CollisionException() 
            : std::runtime_error("CollisionException: Wykrycie nakladania sie wspolrzednych przestrzennych dwoch obiektow typu Train poza bezpiecznymi stacjami wezlowymi.") {}

        /**
         * @brief Konstruktor pozwalający na doprecyzowanie okoliczności kolizji.
         * @param message Spersonalizowany komunikat (np. zawierający ID pociągów uczestniczących w wypadku).
         */
        explicit CollisionException(const std::string& message) 
            : std::runtime_error(message) {}
    };

}