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
        // W przyszłości: wywołanie algorytmu wyznaczania tras po grafie
        std::cout << "[TrackNetwork] Przeliczanie tras dla " 
                  << activeTrains.size() << " aktywnych pociagow...\n";
    }

    bool TrackNetwork::checkCollisions() {
        // Naiwny algorytm sprawdzania kolizji na potrzeby początkowych testów integracyjnych
        for (size_t i = 0; i < activeTrains.size(); ++i) {
            for (size_t j = i + 1; j < activeTrains.size(); ++j) {
                
                // Zmienna testowa - docelowo będziecie tu sprawdzać współrzędne X,Y obiektów
                bool collisionDetected = false; 

                if (collisionDetected) {
                    throw CollisionException();
                }
            }
        }
        return false;
    }

} // namespace Logistics