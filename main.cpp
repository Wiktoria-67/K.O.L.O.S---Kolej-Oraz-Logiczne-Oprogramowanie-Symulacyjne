#include <iostream>
#include <exception>
#include "Core/SimulationEngine.h"
#include "Core/RenderException.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "  K.O.L.O.S. - Start Systemu (Etap 0)   \n";
    std::cout << "========================================\n";

    try {
        // Utworzenie i uruchomienie głównego silnika
        Core::SimulationEngine engine;
        engine.startSimulation();
        
        // Ręczne wywołanie jednego ticku dla testu (docelowo to będzie w pętli while)
        engine.tick(); 

    } catch (const Core::RenderException& e) {
        std::cerr << "[BLAD KRYTYCZNY] " << e.what() << "\n";
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "[NIEZNANY BLAD] " << e.what() << "\n";
        return 2;
    }

    std::cout << "========================================\n";
    std::cout << "  System zamkniety poprawnie.           \n";
    std::cout << "========================================\n";
    return 0;
}