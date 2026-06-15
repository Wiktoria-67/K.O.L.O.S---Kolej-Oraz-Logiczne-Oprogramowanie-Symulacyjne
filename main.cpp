#include "Core/Application.h"
#include <iostream>

int main() {
    try {
        Core::Application app;
        app.run();
    } catch (const std::exception& e) {
        std::cerr << "\n[BLAD KRYTYCZNY] Program zakonczony awaryjnie: " << e.what() << "\n";
        return -1;
    }
    return 0;
}