#pragma once
#include <vector>
// Deklaracja wyprzedzająca, aby uniknąć zapętlenia nagłówków.
// Pełny "#include "Train.h"" znajdzie się w pliku TrackNetwork.cpp
namespace Logistics { class Train; } 

namespace Logistics {

    class TrackNetwork {
    private:
        // Kontener przechowujący wskaźniki na pociągi operujące w sieci
        std::vector<Train*> activeTrains;
        
        // Tutaj w przyszłości znajdzie się struktura grafu połączeń (np. wektor węzłów i krawędzi)
        // std::vector<Node> nodes;

    public:
        TrackNetwork() = default;
        ~TrackNetwork() = default;

        // Dodaje pociąg do sieci monitorowanej przez TrackNetwork
        void registerTrain(Train* train);

        // Przelicza trasy i aktualizuje ścieżki dla pociągów
        void calculateRoutes();

        // Sprawdza pozycje pociągów pod kątem kolizji.
        // Jeśli wykryje nakładanie się współrzędnych, rzuca CollisionException.
        bool checkCollisions();
    };

} // namespace Logistics