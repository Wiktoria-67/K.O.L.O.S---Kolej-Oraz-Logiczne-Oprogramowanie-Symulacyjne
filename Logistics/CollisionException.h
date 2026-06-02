#pragma once
#include <stdexcept>
#include <string>

namespace Logistics {

    class CollisionException : public std::runtime_error {
    public:
        // Konstruktor domyślny z komunikatem bazującym na specyfikacji
        CollisionException() 
            : std::runtime_error("CollisionException: Wykrycie nakladania sie wspolrzednych przestrzennych dwoch obiektow typu Train poza bezpiecznymi stacjami wezlowymi.") {}

        // Opcjonalny konstruktor pozwalający na doprecyzowanie komunikatu (np. ID pociagow)
        explicit CollisionException(const std::string& message) 
            : std::runtime_error(message) {}
    };

}