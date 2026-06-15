#include <gtest/gtest.h>
#include "../Logistics/Route.h"
#include "../Logistics/SmallTrain.h"
#include "../Logistics/MediumTrain.h"
#include "../Logistics/LargeTrain.h"
#include "../Logistics/TrackNetwork.h"
#include "../Logistics/CapacityExceededException.h"
#include "../Logistics/CollisionException.h"
#include "../Industry/PowerPlant.h"
#include "../Industry/SteelMill.h"
#include "../Industry/MachineFactory.h"
#include "../Industry/CoalMine.h"
#include "../Industry/IronMine.h"
#include "../Industry/EmptyStorageException.h"
#include "../Core/SharedTypes.h"
#include "../Core/Button.h"
#include "../Core/InfoPanel.h"
#include "../Core/SimulationEngine.h"
#include <memory>

// ==========================================
// TESTY MODUŁU: LOGISTYKA - TRASA
// ==========================================

TEST(RouteTest, NewlyCreatedRouteIsEmpty) {
    Logistics::Route route;
    EXPECT_TRUE(route.isEmpty());
}

TEST(RouteTest, CanAddWaypointsToRoute) {
    Logistics::Route route;

    route.addWaypoint({10, 20});

    EXPECT_FALSE(route.isEmpty());
    EXPECT_EQ(route.getWaypoints().size(), 1);

    EXPECT_EQ(route.getWaypoints().front().x, 10);
    EXPECT_EQ(route.getWaypoints().front().y, 20);
}

// ==========================================
// TESTY MODUŁU: LOGISTYKA - POJEMNOŚĆ POCIĄGÓW
// ==========================================

TEST(TrainTest, MediumTrainCapacityEnforced) {
    Logistics::MediumTrain train;

    // MediumTrain ma maxCapacity = 5. Ładujemy 5 razy.
    for(int i = 0; i < 5; ++i) {
        EXPECT_NO_THROW(train.loadResource());
    }

    // Szósta próba musi rzucić wyjątek
    EXPECT_THROW(train.loadResource(), Logistics::CapacityExceededException);
}

TEST(TrainTest, LargeTrainCapacityEnforced) {
    Logistics::LargeTrain train;

    // LargeTrain ma maxCapacity = 12. Ładujemy 12 razy.
    for(int i = 0; i < 12; ++i) {
        EXPECT_NO_THROW(train.loadResource());
    }

    // Trzynasta próba musi rzucić wyjątek
    EXPECT_THROW(train.loadResource(), Logistics::CapacityExceededException);
}

// ==========================================
// TESTY MODUŁU: LOGISTYKA - RUCH I AKTUALIZACJA
// ==========================================

TEST(TrainTest, TrainMovesTowardsTargetBasedOnSpeed) {
    Logistics::SmallTrain train; // Prędkość SmallTrain wynosi 10.0f
    Logistics::Route route;

    // Trasa: start na X:0, meta na X:25
    route.addWaypoint({0, 0});
    route.addWaypoint({25, 0});

    train.setRoute(route);

    // Upewniamy się, że pociąg wskoczył na stację początkową (korzystając z gettera)
    EXPECT_EQ(train.getPosition().x, 0);
    EXPECT_EQ(train.getPosition().y, 0);

    // Tick 1: Pociąg orientuje się, że jest na węźle startowym i podbija cel na węzeł (1)
    train.update();
    EXPECT_EQ(train.getPosition().x, 0); // Stoi w miejscu

    // Tick 2: Pociąg rusza (prędkość: 3)
    train.update();
    EXPECT_EQ(train.getPosition().x, 3);

    // Tick 3: Pociąg jedzie dalej (pozycja: 6)
    train.update();
    EXPECT_EQ(train.getPosition().x, 6);

    // Tick 4: Pociąg jedzie dalej (pozycja: 9)
    train.update();
    EXPECT_EQ(train.getPosition().x, 9);
}

// ==========================================
// TESTY MODUŁU: LOGISTYKA - SIEC TORÓW I KOLIZJE
// ==========================================

TEST(TrackNetworkTest, CanRegisterTrainsWithoutCrashing) {
    Logistics::TrackNetwork network;
    Logistics::SmallTrain t1;
    Logistics::LargeTrain t2;

    EXPECT_NO_THROW(network.registerTrain(&t1));
    EXPECT_NO_THROW(network.registerTrain(&t2));
}

TEST(TrackNetworkTest, CollisionCheckReturnsFalseWhenNoCollisions) {
    Logistics::TrackNetwork network;
    Logistics::MediumTrain t1;
    Logistics::MediumTrain t2;

    // Rozsuwamy pociągi korzystając z bezpiecznej enkapsulacji (setterów)
    t1.setPosition({10, 10});
    t2.setPosition({50, 50});

    network.registerTrain(&t1);
    network.registerTrain(&t2);

    // Nie nakładają się, więc kolizji brak
    EXPECT_FALSE(network.checkCollisions());
}

TEST(TrackNetworkTest, CollisionCheckThrowsOnOverlap) {
    Logistics::TrackNetwork network;
    Logistics::MediumTrain t1;
    Logistics::MediumTrain t2;

    // Wymuszamy fizyczne nałożenie się obiektów
    t1.setPosition({100, 100});
    t2.setPosition({100, 100});

    network.registerTrain(&t1);
    network.registerTrain(&t2);

    // System musi to bezwzględnie wykryć i rzucić odpowiedni wyjątek
    EXPECT_THROW(network.checkCollisions(), Logistics::CollisionException);
}

// ==========================================
// TESTY MODUŁU: PRZEMYSŁ - FABRYKI I WYJĄTKI
// ==========================================

TEST(FactoryTest, PowerPlantThrowsWhenEmpty) {
    Industry::PowerPlant plant;
    // Puste bufory - wyjątek z obsługi enkapsulacji
    EXPECT_THROW(plant.processResources(), Industry::EmptyStorageException);
}

TEST(FactoryTest, SteelMillThrowsWhenEmpty) {
    Industry::SteelMill mill;
    // Huta przywołuje gettery - przy pustych wyrzuci błąd logiki
    EXPECT_THROW(mill.processResources(), Industry::EmptyStorageException);
}

TEST(FactoryTest, FactoryUpdateCatchesException) {
    Industry::MachineFactory factory;
    // Pętla update ma try-catch, co czyni ją bezpieczną dla silnika
    EXPECT_NO_THROW(factory.update());
}

// ==========================================
// TESTY MODUŁU: PRZEMYSŁ - KOPALNIE I TIMERY
// ==========================================

TEST(MineTest, CoalMineUpdateLoopExecutesSafely) {
    Industry::CoalMine mine;
    for(int i = 0; i < 60; ++i) {
        EXPECT_NO_THROW(mine.update());
    }
}

TEST(MineTest, IronMineUpdateLoopExecutesSafely) {
    Industry::IronMine mine;
    for(int i = 0; i < 100; ++i) {
        EXPECT_NO_THROW(mine.update());
    }
}

// ==========================================
// TESTY MODUŁU: CORE - STRUKTURY BAZOWE
// ==========================================

TEST(CoreTest, Point2DEqualityOperatorWorks) {
    Core::Point2D p1{10, 20};
    Core::Point2D p2{10, 20};
    Core::Point2D p3{15, 20};

    EXPECT_TRUE(p1 == p2);
    EXPECT_FALSE(p1 == p3);
}

// ==========================================
// TESTY MODUŁU: CORE - INTERFEJS UŻYTKOWNIKA
// ==========================================

TEST(UITest, ButtonDetectsClickInsideHitbox) {
    Core::Button btn(10, 20, 100, 50, sf::Color::Red, "Test");

    EXPECT_TRUE(btn.onClick(60, 45));
    EXPECT_TRUE(btn.onClick(10, 20));
    EXPECT_TRUE(btn.onClick(110, 70));

    EXPECT_FALSE(btn.onClick(5, 45));
    EXPECT_FALSE(btn.onClick(60, 10));
    EXPECT_FALSE(btn.onClick(115, 75));
}

TEST(UITest, InfoPanelIgnoresClicks) {
    Core::InfoPanel panel;
    EXPECT_FALSE(panel.onClick(0, 0));
    EXPECT_FALSE(panel.onClick(999, 999));
}

// ==========================================
// TESTY MODUŁU: CORE - SILNIK SYMULACJI
// ==========================================

class DummyMapObject : public Core::MapObject {
public:
    bool wasUpdated = false;

    void draw(sf::RenderWindow& window) override {}

    void update() override {
        wasUpdated = true;
    }
};

TEST(SimulationEngineTest, TickUpdatesAllRegisteredObjects) {
    Core::SimulationEngine engine;

    auto dummy1 = std::make_unique<DummyMapObject>();
    auto dummy2 = std::make_unique<DummyMapObject>();

    DummyMapObject* ptr1 = dummy1.get();
    DummyMapObject* ptr2 = dummy2.get();

    engine.mapObjects.push_back(std::move(dummy1));
    engine.mapObjects.push_back(std::move(dummy2));

    EXPECT_FALSE(ptr1->wasUpdated);
    EXPECT_FALSE(ptr2->wasUpdated);

    engine.tick();

    EXPECT_TRUE(ptr1->wasUpdated);
    EXPECT_TRUE(ptr2->wasUpdated);
}

// ==========================================
// TEST INTEGRACYJNY: PEŁNY ŁAŃCUCH DOSTAW
// ==========================================

TEST(SupplyChainIntegrationTest, FullExtractionTransportAndProductionCycle) {
    // 1. Aranżacja: Tworzymy infrastrukturę w tym samym punkcie (X:10, Y:10)
    Industry::CoalMine mine;
    Industry::PowerPlant plant;
    Logistics::MediumTrain train;

    mine.setPosition({10, 10});
    plant.setPosition({10, 10});
    train.setPosition({10, 10});

    // 2. Symulacja wydobycia: CoalMine potrzebuje 50 ticków na wykopanie węgla
    for(int i = 0; i < 60; ++i) {
        mine.update();
    }
    EXPECT_EQ(mine.getOutputBuffer(), 1); // Kopalnia powinna mieć 1 węgiel

    // 3. Symulacja załadunku: Pociąg podjeżdża i pobiera surowiec
    EXPECT_EQ(train.getCurrentCapacity(), 0);
    train.loadFromMine(mine);

    EXPECT_EQ(mine.getOutputBuffer(), 0); // Kopalnia oczyszczona
    EXPECT_EQ(train.getCurrentCapacity(), 1); // Pociąg załadowany

    // 4. Symulacja rozładunku: Pociąg przekazuje węgiel do Elektrowni (Bufor A)
    EXPECT_EQ(plant.getInputBufferA(), 0);
    train.unloadToFactory(plant, false); // false = do Bufora A

    EXPECT_EQ(train.getCurrentCapacity(), 0); // Pociąg znowu pusty
    EXPECT_EQ(plant.getInputBufferA(), 1); // Elektrownia ma węgiel!

    // 5. Symulacja produkcji: Silnik wywołuje update na fabryce, która spala węgiel
    EXPECT_NO_THROW(plant.update());
    EXPECT_EQ(plant.getInputBufferA(), 0); // Węgiel został pomyślnie skonsumowany!
}