#pragma once
#include <stdexcept>

namespace Industry {

    class EmptyStorageException : public std::logic_error {
    public:
        // Tylko deklaracja konstruktora, brak nawiasów klamrowych {}
        EmptyStorageException(); 
    };

} // namespace Industry