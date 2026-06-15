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

    // Upewniamy się, że pociąg wskoczył na stację początkową
    EXPECT_EQ(train.getPosition().x, 0);
    EXPECT_EQ(train.getPosition().y, 0);

    // Tick 1: Pociąg orientuje się, że jest na węźle startowym (0) i podbija cel na węzeł (1)
    train.update();
    EXPECT_EQ(train.getPosition().x, 0); // Stoi w miejscu

    // Tick 2: Pociąg faktycznie rusza w trasę (prędkość 10)
    train.update();
    EXPECT_EQ(train.getPosition().x, 10);

    // Tick 3: Pociąg jedzie dalej
    train.update();
    EXPECT_EQ(train.getPosition().x, 20);

    // Tick 4: Dociera do celu (zostało mu 5 dystansu do 25, a prędkość to 10)
    train.update();
    EXPECT_EQ(train.getPosition().x, 25);
}
// ==========================================
// TESTY MODUŁU: LOGISTYKA - SIEC TORÓW
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

    network.registerTrain(&t1);
    network.registerTrain(&t2);

    EXPECT_FALSE(network.checkCollisions());
}

// ==========================================
// TESTY MODUŁU: PRZEMYSŁ - FABRYKI I WYJĄTKI
// ==========================================

TEST(FactoryTest, PowerPlantThrowsWhenEmpty) {

    Industry::PowerPlant plant;

    EXPECT_THROW(plant.processResources(), Industry::EmptyStorageException);
}

TEST(FactoryTest, SteelMillThrowsWhenEmpty) {
    Industry::SteelMill mill;
    // Huta wymaga dwóch surowców, więc przy pustych buforach również powinna zgłosić błąd logiki
    EXPECT_THROW(mill.processResources(), Industry::EmptyStorageException);
}

TEST(FactoryTest, FactoryUpdateCatchesException) {
    Industry::MachineFactory factory;

    // Metoda update() w klasie bazowej Factory posiada wbudowany blok try-catch.
    // Oznacza to, że z perspektywy głównej pętli gry (SimulationEngine),
    // wywołanie update() na pustej fabryce powinno być w 100% bezpieczne.
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
    // Tworzymy przycisk: X: 10, Y: 20, Szerokość: 100, Wysokość: 50
    Core::Button btn(10, 20, 100, 50, sf::Color::Red);

    // Kliknięcia idealnie w środku
    EXPECT_TRUE(btn.onClick(60, 45));

    // Kliknięcia na krawędziach (zgodnie z kodem >= i <= powinny zwracać true)
    EXPECT_TRUE(btn.onClick(10, 20)); // Lewy górny róg
    EXPECT_TRUE(btn.onClick(110, 70)); // Prawy dolny róg

    // Kliknięcia poza przyciskiem
    EXPECT_FALSE(btn.onClick(5, 45));  // Za daleko w lewo
    EXPECT_FALSE(btn.onClick(60, 10)); // Za wysoko
    EXPECT_FALSE(btn.onClick(115, 75)); // Całkowicie poza zasięgiem
}

TEST(UITest, InfoPanelIgnoresClicks) {
    Core::InfoPanel panel;
    // InfoPanel ma zawsze ignorować kliknięcia
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

    // Tworzymy dwa testowe obiekty
    auto dummy1 = std::make_unique<DummyMapObject>();
    auto dummy2 = std::make_unique<DummyMapObject>();

    // Zapisujemy nagie wskaźniki, by móc sprawdzić ich stan po oddaniu do silnika
    DummyMapObject* ptr1 = dummy1.get();
    DummyMapObject* ptr2 = dummy2.get();

    engine.addMapObject(std::move(dummy1));
    engine.addMapObject(std::move(dummy2));

    // Przed wywołaniem tick(), obiekty nie powinny być zaktualizowane
    EXPECT_FALSE(ptr1->wasUpdated);
    EXPECT_FALSE(ptr2->wasUpdated);

    // Wywołujemy jedną klatkę symulacji
    engine.tick();

    // Silnik powinien przejść po wektorze i wywołać update() na obu obiektach
    EXPECT_TRUE(ptr1->wasUpdated);
    EXPECT_TRUE(ptr2->wasUpdated);
}