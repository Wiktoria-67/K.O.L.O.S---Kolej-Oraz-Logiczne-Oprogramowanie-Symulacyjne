#include <gtest/gtest.h>

// ==========================================
// NAGŁÓWKI - CORE
// ==========================================
#include "../Core/SharedTypes.h"
#include "../Core/RenderException.h"
#include "../Core/SimulationEngine.h"
#include "../Core/Button.h"
#include "../Core/InfoPanel.h"
#include "../Core/MapObject.h"

// ==========================================
// NAGŁÓWKI - LOGISTYKA
// ==========================================
#include "../Logistics/MediumTrain.h"
#include "../Logistics/Route.h"
#include "../Logistics/TrackNetwork.h"
#include "../Logistics/CapacityExceededException.h"
#include "../Logistics/CollisionException.h"

// ==========================================
// NAGŁÓWKI - PRZEMYSŁ
// ==========================================
#include "../Industry/EmptyStorageException.h"
#include "../Industry/CoalMine.h"
#include "../Industry/IronMine.h"
#include "../Industry/PowerPlant.h"
#include "../Industry/SteelMill.h"
#include "../Industry/MachineFactory.h"

// ==========================================
// TESTY DLA CORE (Rdzeń i UI)
// ==========================================

namespace Core {
namespace Tests {

// --- TESTY SHARED TYPES ---
TEST(Point2DTest, EqualityOperatorComparesCoordinatesCorrectly) {
    Point2D p1{100, 200};
    Point2D p2{100, 200};
    Point2D p3{150, 200};
    Point2D p4{100, 250};

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
    EXPECT_FALSE(p1 == p4);
}

// --- TESTY EXCEPTIONS ---
TEST(RenderExceptionTest, WhatReturnsCorrectErrorMessage) {
    RenderException ex;
    EXPECT_STREQ(ex.what(), "RenderException: Niepowodzenie ladowania zasobow graficznych.");
}

// --- TESTY UI: BUTTON ---
TEST(ButtonTest, OnClickDetectsHitboxCorrectly) {
    // Przycisk na pozycji (10, 10) o wymiarach 100x50
    Button btn(10, 10, 100, 50, sf::Color::Red, "Test");

    // Kliknięcia wewnątrz i na krawędziach (AABB)
    EXPECT_TRUE(btn.onClick(15, 15));
    EXPECT_TRUE(btn.onClick(10, 10)); // Górny lewy róg
    EXPECT_TRUE(btn.onClick(110, 60)); // Dolny prawy róg

    // Kliknięcia poza przyciskiem
    EXPECT_FALSE(btn.onClick(5, 5));
    EXPECT_FALSE(btn.onClick(111, 60));
    EXPECT_FALSE(btn.onClick(50, 9));
}

// --- TESTY UI: INFOPANEL ---
TEST(InfoPanelTest, OnClickAlwaysReturnsFalse) {
    InfoPanel panel;
    EXPECT_FALSE(panel.onClick(0, 0));
    EXPECT_FALSE(panel.onClick(500, 500));
}

// --- TESTY MAP OBJECT (Abstrakcja) ---
// Klasa pomocnicza do testowania MapObject
class DummyMapObject : public MapObject {
public:
    void draw(sf::RenderWindow& window) override {}
    void update() override {}
};

TEST(MapObjectTest, GettersAndSettersWorkCorrectly) {
    DummyMapObject obj;
    obj.setPosition({42, 84});
    
    EXPECT_EQ(obj.getPosition().x, 42);
    EXPECT_EQ(obj.getPosition().y, 84);
}

// --- TESTY SILNIKA SYMULACJI ---
TEST(SimulationEngineTest, InitialStateIsCorrect) {
    SimulationEngine engine;
    
    EXPECT_EQ(engine.tickCounter, 0);
    EXPECT_TRUE(engine.mapObjects.empty());
    EXPECT_TRUE(engine.allRoutes.empty());
    
    EXPECT_EQ(engine.pointerToCoalMine, nullptr);
    EXPECT_EQ(engine.pointerToIronMine, nullptr);
    EXPECT_EQ(engine.pointerToFactory, nullptr);
    EXPECT_EQ(engine.pointerToPowerPlant, nullptr);
    EXPECT_EQ(engine.pointerToMachineFactory, nullptr);
}

TEST(SimulationEngineTest, TickIncrementsGlobalCounter) {
    SimulationEngine engine;
    
    EXPECT_EQ(engine.tickCounter, 0);
    engine.tick();
    EXPECT_EQ(engine.tickCounter, 1);
    engine.tick();
    engine.tick();
    EXPECT_EQ(engine.tickCounter, 3);
}

} // namespace Tests
} // namespace Core


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

// ==========================================
// TESTY DLA MODUŁU PRZEMYSŁOWEGO (INDUSTRY)
// ==========================================

namespace Industry {
namespace Tests {

// --- TESTY KOPALNI (Mine) ---
TEST(CoalMineTest, GeneratesResourceAfter50Ticks) {
    CoalMine mine;
    EXPECT_EQ(mine.getOutputBuffer(), 0);

    // Symulacja 50 ticków (zbijamy timer dokładnie do zera)
    for (int i = 0; i < 50; ++i) {
        mine.update();
    }
    EXPECT_EQ(mine.getOutputBuffer(), 0); // Timer to 0, ale jeszcze nie wygenerowano

    mine.update();
    EXPECT_EQ(mine.getOutputBuffer(), 1);
}

TEST(IronMineTest, GeneratesResourceAfter80Ticks) {
    IronMine mine;
    
    for (int i = 0; i < 81; ++i) {
        mine.update();
    }
    EXPECT_EQ(mine.getOutputBuffer(), 1);
}

TEST(MineBufferTest, OutputBufferValidation) {
    CoalMine mine;
    // Dodawanie ujemnych wartości powinno być ignorowane
    mine.increaseOutputBuffer(-5);
    EXPECT_EQ(mine.getOutputBuffer(), 0);

    mine.increaseOutputBuffer(10);
    EXPECT_EQ(mine.getOutputBuffer(), 10);

    // Zmniejszanie o wartość większą niż stan magazynu powinno zostać zignorowane
    mine.decreaseOutputBuffer(15);
    EXPECT_EQ(mine.getOutputBuffer(), 10);

    mine.decreaseOutputBuffer(3);
    EXPECT_EQ(mine.getOutputBuffer(), 7);
}

// --- TESTY FABRYK I BUFORÓW (Factory) ---

TEST(FactoryBufferTest, InputBufferValidation) {
    SteelMill mill;
    mill.addInputA(-10); // Ignorowane
    EXPECT_EQ(mill.getInputBufferA(), 0);

    mill.addInputA(5);
    EXPECT_EQ(mill.getInputBufferA(), 5);

    // Próba konsumpcji większej ilości niż jest w buforze powinna rzucić wyjątek
    EXPECT_THROW(mill.consumeInputA(10), EmptyStorageException);
    
    // Pomyślna konsumpcja
    EXPECT_NO_THROW(mill.consumeInputA(3));
    EXPECT_EQ(mill.getInputBufferA(), 2);
}

// --- TESTY ELEKTROWNI (PowerPlant) ---

TEST(PowerPlantTest, GeneratesEnergyWhenCoalIsPresent) {
    PowerPlant plant;
    plant.addInputA(1); // Dodajemy 1 węgiel

    EXPECT_NO_THROW(plant.processResources());
    EXPECT_EQ(plant.getInputBufferA(), 0);
    EXPECT_EQ(plant.getGeneratedEnergy(), 10);
}

TEST(PowerPlantTest, ThrowsWhenNoCoal) {
    PowerPlant plant;
    EXPECT_THROW(plant.processResources(), EmptyStorageException);
    EXPECT_EQ(plant.getGeneratedEnergy(), 0);
}

TEST(PowerPlantTest, EnergyConsumption) {
    PowerPlant plant;
    plant.addInputA(2);
    plant.processResources(); // +10 energii
    plant.processResources(); // +10 energii (razem 20)

    plant.consumeEnergy(5);
    EXPECT_EQ(plant.getGeneratedEnergy(), 15);

    // Próba zużycia więcej niż jest nie powinna zmienić stanu
    plant.consumeEnergy(20);
    EXPECT_EQ(plant.getGeneratedEnergy(), 15);
}

// --- TESTY HUTY STALI (SteelMill) ---

TEST(SteelMillTest, ProducesSteelWithSufficientResources) {
    SteelMill mill;
    mill.addInputA(1); // Węgiel
    mill.addInputB(1); // Ruda

    EXPECT_NO_THROW(mill.processResources());
    EXPECT_EQ(mill.getInputBufferA(), 0);
    EXPECT_EQ(mill.getInputBufferB(), 0);
    EXPECT_EQ(mill.getOutputBuffer(), 1); // Wyprodukowano 1 stal
}

TEST(SteelMillTest, ThrowsWhenMissingResources) {
    SteelMill mill;
    mill.addInputA(1); // Tylko węgiel, brak rudy
    
    EXPECT_THROW(mill.processResources(), EmptyStorageException);
    EXPECT_EQ(mill.getOutputBuffer(), 0);
}

// --- TESTY ZAAWANSOWANEJ FABRYKI (MachineFactory) ---

TEST(MachineFactoryTest, ThrowsWithoutPowerGrid) {
    MachineFactory factory;
    factory.addInputA(1); // Stal jest, ale nie ma prądu

    EXPECT_THROW(factory.processResources(), EmptyStorageException);
}

TEST(MachineFactoryTest, ThrowsWithInsufficientEnergy) {
    PowerPlant plant;
    // Elektrownia pusta, ma 0 energii

    MachineFactory factory;
    factory.connectToGrid(&plant);
    factory.addInputA(1);

    EXPECT_THROW(factory.processResources(), EmptyStorageException);
}

TEST(MachineFactoryTest, ProducesVictoryPointsWithSteelAndPower) {
    PowerPlant plant;
    plant.addInputA(1);
    plant.processResources(); // Generuje 10 energii

    MachineFactory factory;
    factory.connectToGrid(&plant);
    factory.addInputA(1); // Dodajemy stal

    EXPECT_NO_THROW(factory.processResources());
    
    // Sprawdzamy efekty
    EXPECT_EQ(factory.getVictoryPoints(), 50);
    EXPECT_EQ(plant.getGeneratedEnergy(), 0); // Zużyto 10 energii
    EXPECT_EQ(factory.getInputBufferA(), 0);  // Zużyto stal
}

} // namespace Tests
} // namespace Industry