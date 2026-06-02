#include "Renderer.h"
#include <iostream>

namespace Core {

    void Renderer::initWindow() {
        std::cout << "[Renderer] Okno graficzne zostalo zainicjalizowane (Tryb testowy).\n";
    }

    void Renderer::renderAll(const std::vector<std::unique_ptr<IDrawable>>& drawables) {
        std::cout << "[Renderer] Przeskanowano obiekty do wyrysowania. Liczba obiektow: " 
                  << drawables.size() << "\n";
    }

} // namespace Core