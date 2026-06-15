#pragma once
#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>

#include "Renderer.h"
#include "SimulationEngine.h"
#include "Button.h"
#include "InfoPanel.h"
#include "../Logistics/Route.h"

/**
 * @namespace Core
 * @brief Przestrzeń nazw zawierająca kluczowe komponenty strukturalne i interfejsu aplikacji.
 */
namespace Core {

/**
 * @enum BuildMode
 * @brief Tryby interakcji użytkownika określające, jaki obiekt jest aktualnie budowany lub konfigurowany.
 */
enum class BuildMode {
    None,           /**< Brak aktywnego trybu budowania. */
    CoalMine,       /**< Tryb stawiania kopalni węgla. */
    IronMine,       /**< Tryb stawiania kopalni rudy żelaza. */
    Factory,        /**< Tryb stawiania huty stali. */
    PowerPlant,     /**< Tryb stawiania elektrowni. */
    MachineFactory, /**< Tryb stawiania fabryki maszyn. */
    Route           /**< Tryb wytyczania nowej trasy kolejowej. */
};

/**
 * @class Application
 * @brief Główna klasa zarządzająca cyklem życia programu, oknem graficznym oraz interfejsem użytkownika.
 * * Klasa integruje bibliotekę SFML z silnikiem symulacji, odpowiada za przechwytywanie
 * zdarzeń wejściowych, rysowanie klatek oraz koordynację głównej pętli aplikacji.
 */
class Application {
private:
    Renderer renderer; ///< Komponent odpowiedzialny za inicjalizację i zarządzanie oknem graficznym. */
    SimulationEngine engine; ///< Silnik symulacyjny przechowujący stan świata gry i jego logikę.
    std::unique_ptr<InfoPanel> infoPanel; ///< Inteligentny wskaźnik na panel informacyjny interfejsu użytkownika.

    // Interfejs użytkownika
    sf::RectangleShape sidebarPanel; ///< Kształt reprezentujący tło bocznego panelu menu.
    sf::Font font; ///< Czcionka używana do renderowania tekstów interfejsu.
    sf::Text statsText; ///< Obiekt tekstowy wyświetlający bieżące statystyki (energia, punkty).
    std::vector<std::unique_ptr<Button>> guiButtons; ///< Kontener przechowujący przyciski menu bocznego.

    // Stan interakcji użytkownika
    BuildMode currentBuildMode = BuildMode::None; ///< Aktualnie wybrany tryb budowania.
    Logistics::Route customRoute; ///< Instancja trasy tymczasowo modyfikowanej podczas rysowania przez gracza.
    int selectedRouteIndex = -1; ///< Indeks obecnie zaznaczonej trasy w systemie (-1 oznacza brak selekcji).

    // Wewnętrzne metody pomocnicze
    /**
     * @brief Inicjalizuje i konfiguruje elementy graficzne interfejsu użytkownika (UI).
     * * Odpowiada za ustawienie pozycji paneli, załadowanie czcionek, konfigurację pól tekstowych
     * oraz dynamiczne utworzenie obiektów przycisków w menu bocznym.
     */
    void setupUI();

    /**
     * @brief Przechwytuje i przetwarza zdarzenia systemowe oraz wejściowe z okna SFML.
     * * Obsługuje m.in. zamknięcie aplikacji, kliknięcia myszką w obszarze menu bocznego
     * (zarządzanie trybami budowania) oraz kliknięcia na mapie (stawianie budynków i tras).
     */
    void handleEvents();

    /**
     * @brief Odpowiada za czyszczenie ekranu i rysowanie wszystkich obiektów graficznych.
     * * Renderuje w odpowiedniej kolejności: tło, obiekty na mapie (budynki, pociągi), trasy,
     * panel boczny, przyciski interfejsu, teksty statystyk oraz opcjonalne tooltipy.
     */
    void render();

    /**
     * @brief Rysuje kontekstowe dymki informacyjne (tooltipy) nad obiektami mapy.
     * @param window Referencja do okna renderowania SFML.
     * @param mousePos Aktualna pozycja kursora myszy względem okna.
     */
    void drawTooltips(sf::RenderWindow& window, sf::Vector2i mousePos);

public:
    /**
     * @brief Konstruktor klasy Application.
     * * Inicjalizuje podstawowe komponenty, uruchawia konfigurację UI i przygotowuje aplikację do pracy.
     */
    Application();

    /**
     * @brief Uruchamia główną pętlę symulacji i aplikacji.
     * * Metoda blokująca, która wykonuje się aż do momentu zamknięcia okna programu.
     * W każdej iteracji wywołuje obsługę zdarzeń, krok logiczny silnika oraz renderowanie grafiki.
     */
    void run();
};
} // namespace Core