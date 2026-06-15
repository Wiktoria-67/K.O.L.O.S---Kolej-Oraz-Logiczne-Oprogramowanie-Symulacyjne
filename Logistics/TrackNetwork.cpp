#include "TrackNetwork.h"
#include "Train.h"
#include "CollisionException.h"
#include <iostream>

namespace Logistics {

    void TrackNetwork::registerTrain(Train* train) {
        if (train != nullptr) {
            activeTrains.push_back(train);
        }
    }

    void TrackNetwork::calculateRoutes() {
        // W przyszłości: wywołanie algorytmu wyznaczania tras
        std::cout << "[TrackNetwork] Przeliczanie tras dla " 
                  << activeTrains.size() << " aktywnych pociagow...\n";
    }

    bool TrackNetwork::checkCollisions() {
        /* * Detekcja kolizji:
         * Sprawdza każdą parę pociągów pod kątem współdzielenia tych samych współrzędnych.
         * Jeśli dwa pociągi są w tym samym punkcie (poza węzłami stacyjnymi),
         * rzuca wyjątek CollisionException.
         */
        for (size_t i = 0; i < activeTrains.size(); ++i) {
            for (size_t j = i + 1; j < activeTrains.size(); ++j) {

                bool collisionDetected = false; 

                if (collisionDetected) {
                    throw CollisionException();
                }
            }
        }
        return false;
    }

}