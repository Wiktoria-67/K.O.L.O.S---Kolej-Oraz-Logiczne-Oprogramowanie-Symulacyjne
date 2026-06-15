#pragma once
#include <vector>

namespace Logistics { class Train; } 

namespace Logistics {

    /**
     * @class TrackNetwork
     * @brief Centralny system zarządzający infrastrukturą kolejową.
     * * Nadzoruje aktywne pociągi, wyznacza ich ścieżki i dba o unikanie
     * kolizji w przestrzeni symulacyjnej.
     */
    class TrackNetwork {
    private:

        std::vector<Train*> activeTrains; ///< Wektor wskaźników na pociągi zarejestrowane w sieci.
        
        // Tutaj w przyszłości znajdzie się struktura grafu połączeń (np. wektor węzłów i krawędzi)
        // std::vector<Node> nodes;

    public:
        TrackNetwork() = default;
        ~TrackNetwork() = default;

        /**
         * @brief Rejestruje nowy pociąg w systemie nadzoru.
         * @param train Wskaźnik na obiekt pociągu. Jeśli nullptr, zostanie zignorowany.
         */
        void registerTrain(Train* train);

        /**
         * @brief Przelicza trasy i optymalizuje ścieżki dla zarejestrowanych pociągów.
         */
        void calculateRoutes();

        /**
         * @brief Sprawdza pozycje pociągów pod kątem kolizji przestrzennych.
         * @return False jeśli nie wykryto kolizji.
         * @throw CollisionException Jeśli współrzędne dwóch pociągów nałożą się poza stacją.
         */
        bool checkCollisions();
    };

}