#include <gtest/gtest.h>
#include "../Core/SharedTypes.h"
#include "../Logistics/MediumTrain.h"
#include "../Logistics/Route.h"
#include "../Logistics/TrackNetwork.h"
#include "../Logistics/CapacityExceededException.h"
#include "../Logistics/CollisionException.h"

// ==========================================
// TESTY DLA MEDIUM TRAIN (Główna jednostka)
// ==========================================

TEST(MediumTrainTest, InitialStateIsCorrect) {
    Logistics::MediumTrain train;
    
    // Pociąg na starcie powinien być pusty
    EXPECT_EQ(train.getCurrentCapacity(), 0);
    
    // Domyślnie nowa trasa powinna sprawiać, że pociąg jest "skończony" / nie ma gdzie jechać
    EXPECT_FALSE(train.isFinished());
}

TEST(MediumTrainTest, CanChangeCargoType) {
    Logistics::MediumTrain train;
    
    train.setCargoType(Core::ResourceType::IronOre);
    EXPECT_EQ(train.getCargoType(), Core::ResourceType::IronOre);
    
    train.setCargoType(Core::ResourceType::Steel);
    EXPECT_EQ(train.getCargoType(), Core::ResourceType::Steel);
}

TEST(MediumTrainTest, LoadResourceIncreasesCapacity) {
    Logistics::MediumTrain train;
    int initialCapacity = train.getCurrentCapacity();
    
    train.loadResource();
    
    EXPECT_EQ(train.getCurrentCapacity(), initialCapacity + 1);
}

TEST(MediumTrainTest, ExceedingCapacityThrowsException) {
    Logistics::MediumTrain train;
    
    // MediumTrain ma zdefiniowaną maksymalną pojemność.
    // Próbujemy ładować surowiec w nieskończoność, aż wyrzuci wyjątek.
    EXPECT_THROW({
        for (int i = 0; i < 1000; ++i) {
            train.loadResource();
        }
    }, Logistics::CapacityExceededException);
}

// ==========================================
// TESTY DLA SYSTEMU TRAS (ROUTE)
// ==========================================

TEST(RouteTest, EmptyRouteInitialization) {
    Logistics::Route route;
    EXPECT_TRUE(route.isEmpty());
    EXPECT_EQ(route.getWaypoints().size(), 0);
}

TEST(RouteTest, AddWaypointIncreasesSize) {
    Logistics::Route route;
    route.addWaypoint({100, 200});
    
    EXPECT_FALSE(route.isEmpty());
    EXPECT_EQ(route.getWaypoints().size(), 1);
    EXPECT_EQ(route.getWaypoints()[0].x, 100);
    EXPECT_EQ(route.getWaypoints()[0].y, 200);
}

TEST(RouteTest, TrainFollowsRouteStatus) {
    Logistics::MediumTrain train;
    Logistics::Route route;
    
    route.addWaypoint({50, 50});
    route.addWaypoint({100, 100});
    
    train.setRoute(route);
    
    // Po przypisaniu trasy pociąg ma cel, więc nie jest skończony
    EXPECT_FALSE(train.isFinished());
}

// ==========================================
// TESTY DLA SIECI TORÓW I KOLIZJI
// ==========================================

TEST(TrackNetworkTest, RegisterTrainWorks) {
    Logistics::TrackNetwork network;
    Logistics::MediumTrain train;
    
    // Test sprawdzający, czy metoda rejestracji nie powoduje crasha
    EXPECT_NO_THROW(network.registerTrain(&train));
}

TEST(TrackNetworkTest, DetectsCollisionWhenTrainsAreOnSameSpot) {
    Logistics::TrackNetwork network;
    Logistics::MediumTrain train1;
    Logistics::MediumTrain train2;
    
    // Ustawiamy oba pociągi dokładnie w tym samym miejscu
    train1.setPosition({150, 150});
    train2.setPosition({150, 150});
    
    network.registerTrain(&train1);
    network.registerTrain(&train2);
    
    EXPECT_THROW(network.checkCollisions(), Logistics::CollisionException);
}

TEST(TrackNetworkTest, NoCollisionWhenTrainsAreApart) {
    Logistics::TrackNetwork network;
    Logistics::MediumTrain train1;
    Logistics::MediumTrain train2;
    
    // Ustawiamy pociągi w bezpiecznej odległości
    train1.setPosition({100, 100});
    train2.setPosition({500, 500});
    
    network.registerTrain(&train1);
    network.registerTrain(&train2);
    
    EXPECT_NO_THROW(network.checkCollisions());
}
