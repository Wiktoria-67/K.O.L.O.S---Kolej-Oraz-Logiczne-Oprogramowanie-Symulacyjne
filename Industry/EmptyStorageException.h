#pragma once
#include <stdexcept>

namespace Industry {

    /**
     * @class EmptyStorageException
     * @brief Wyjątek logiczny sygnalizujący wstrzymanie procesu produkcyjnego.
     * * Rzucany przez instancje klasy Factory w momencie, gdy pociągi nie dostarczyły
     * wystarczającej ilości materiałów do przetworzenia.
     */
    class EmptyStorageException : public std::logic_error {
    public:
        /**
         * @brief Tworzy obiekt wyjątku z inżynierskim komunikatem o braku surowców.
         */
        EmptyStorageException(); 
    };

}