#pragma once
#include <vector>
#include <memory>
#include "MapObject.h"
#include "../Logistics/TrackNetwork.h"
#include "../Logistics/Route.h"

/**
 * @namespace Industry
 * @brief Przestrzeń nazw grupująca klasy struktur przemysłowych, takich jak kopalnie i fabryki.
 */
namespace Industry {
class CoalMine; class IronMine; class SteelMill; class PowerPlant; class MachineFactory;
}

namespace Core {

/**
 * @class SimulationEngine
 * @brief Serce logiczne aplikacji, przechowujące stan świata i zarządzające symulacją w czasie dyskretnym.
 * * Klasa odpowiada za gromadzenie wszystkich obiektów fizycznych na mapie, zarządzanie trasami,
 * siecią połączeń logistycznych oraz przetwarzanie kolejnych kroków czasowych (tzw. ticków).
 */
class SimulationEngine {
public:
    // Główne kontenery symulacji
    std::vector<std::unique_ptr<MapObject>> mapObjects; ///< Polimorficzny kontener wszystkich obiektów na mapie (pociągi, budynki).
    Logistics::TrackNetwork trackNetwork; ///< System zarządzania siecią kolejową, rejestracją pojazdów i kolizjami.
    std::vector<Logistics::Route> allRoutes; ///< Kontener wszystkich zdefiniowanych przez użytkownika stałych tras.
    long long tickCounter = 0; ///< Globalny licznik kroków czasowych od momentu startu symulacji.

    // Wskaźniki na obiekty infrastruktury
    Industry::CoalMine* pointerToCoalMine = nullptr; ///< Wskaźnik na główną instancję kopalni węgla.
    Industry::IronMine* pointerToIronMine = nullptr; ///< Wskaźnik na główną instancję kopalni rudy.
    Industry::SteelMill* pointerToFactory = nullptr; ///< Wskaźnik na główną instancję huty stali.
    Industry::PowerPlant* pointerToPowerPlant = nullptr; ///< Wskaźnik na główną instancję elektrowni.
    Industry::MachineFactory* pointerToMachineFactory = nullptr; ///< Wskaźnik na główną instancję fabryki maszyn.

    /**
     * @brief Konstruktor domyślny klasy SimulationEngine.
     */
    SimulationEngine() = default;

    /**
     * @brief Wykonuje pojedynczy krok (tick) logiki całej symulacji.
     * * Przebiega przez wszystkie zarejestrowane obiekty w wektorze `mapObjects`, wywołując ich
     * wewnętrzne metody aktualizacji, inkrementuje globalny licznik czasu oraz wymusza
     * procesy produkcyjne i logistyczne w infrastrukturze.
     */
    void tick();
};
}