#pragma once
#include <exception>

namespace Core {
    class RenderException : public std::exception {
    public:
        const char* what() const noexcept override {
            return "RenderException: Niepowodzenie ladowania zasobow graficznych.";
        }
    };
}