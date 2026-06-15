#pragma once
#include <exception>

namespace Core {

    /**
     * @class RenderException
     * @brief Wyjątek zgłaszany w przypadku krytycznych błędów potoku graficznego.
     */
    class RenderException : public std::exception {
    public:
        /**
         * @brief Zwraca opis błędu renderowania.
         */
        const char* what() const noexcept override {
            return "RenderException: Niepowodzenie ladowania zasobow graficznych.";
        }
    };
}