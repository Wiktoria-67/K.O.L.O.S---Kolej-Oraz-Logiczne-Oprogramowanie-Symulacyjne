#include "EmptyStorageException.h"

namespace Industry {

    // Definicja konstruktora i wywołanie konstruktora klasy bazowej std::logic_error
    EmptyStorageException::EmptyStorageException() 
        : std::logic_error("EmptyStorageException: Brak wymaganych surowcow w buforze wejsciowym.") {
    }

}