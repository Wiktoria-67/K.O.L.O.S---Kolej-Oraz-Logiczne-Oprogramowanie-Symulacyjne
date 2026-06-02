#include <iostream>
#include <exception>
#include <memory>
#include "Core/SimulationEngine.h"
#include "Core/RenderException.h"
#include "Industry/CoalMine.h"
#include "Industry/SteelMill.h"
#include "Logistics/SmallTrain.h"
#include "Logistics/Route.h"

// Użycie standardowej przestrzeni nazw dla całego pliku main.cpp
using namespace std;

int main() {
    cout << "========================================\n";
    cout << "  K.O.L.O.S. - Start Systemu (Etap 0)   \n";
    cout << "========================================\n";

    try {
        Core::SimulationEngine engine;

        // 1. TWORZENIE OBIEKTÓW PRZEMYSŁOWYCH
        auto coalMine = make_unique<Industry::CoalMine>();
        coalMine->setPosition({0, 0}); 
        cout << "[Inicjalizacja] Kopalnia Wegla stoi na X: " 
             << coalMine->getPosition().x << ", Y: " << coalMine->getPosition().y << "\n";

        auto steelMill = make_unique<Industry::SteelMill>();
        steelMill->setPosition({40, 30}); 
        cout << "[Inicjalizacja] Huta (SteelMill) stoi na X: " 
             << steelMill->getPosition().x << ", Y: " << steelMill->getPosition().y << "\n";

        // 2. TWORZENIE POCIĄGU I JEGO TRASY JAKO OBIEKTU
        auto train = make_unique<Logistics::SmallTrain>();
        
        Logistics::Route trainRoute{
            coalMine->getPosition(), // Węzeł 1: Kopalnia
            {40, 0},                 // Węzeł 2: Zakręt
            steelMill->getPosition() // Węzeł 3: Huta
        };
        train->setRoute(trainRoute);

        // 3. WSTRZYKIWANIE ZALEŻNOŚCI DO SILNIKA (DI)
        engine.addMapObject(std::move(coalMine));
        engine.addMapObject(std::move(steelMill));
        engine.addMapObject(std::move(train));

        // 4. URUCHOMIENIE SYMULACJI
        engine.startSimulation();
        
        cout << "\n--- ROZPOCZECIE PETLI TESTOWEJ (45 TICKOW) ---\n";
        for (int i = 1; i <= 10; ++i) {
            cout << "\n--- Tick: " << i << " ---\n";
            engine.tick();
        }
        cout << "--- KONIEC PETLI TESTOWEJ ---\n\n";

    } catch (const Core::RenderException& e) {
        cerr << "[BLAD KRYTYCZNY] " << e.what() << "\n";
        return 1;
    } catch (const exception& e) {
        cerr << "[NIEZNANY BLAD] " << e.what() << "\n";
        return 2;
    }

    cout << "========================================\n";
    cout << "  System zamkniety poprawnie.           \n";
    cout << "========================================\n";
    
    return 0;
}