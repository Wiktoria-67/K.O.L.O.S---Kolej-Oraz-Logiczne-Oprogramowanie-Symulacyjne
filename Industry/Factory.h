#pragma once
#include "../Core/MapObject.h"

/**
 * @namespace Industry
 * @brief Moduł odpowiedzialny za produkcję, wydobycie i przetwarzanie surowców.
 */
namespace Industry {

    /**
     * @class Factory
     * @brief Abstrakcyjna klasa bazowa dla wszystkich fabryk w symulacji.
     * * Dziedziczy po Core::MapObject. Zarządza buforami wejściowymi surowców
     * i definiuje wspólną architekturę procesu produkcyjnego.
     */
    class Factory : public Core::MapObject {
    private:
        int inputBufferA = 0; ///< Bufor przechowujący główny surowiec wejściowy.
        int inputBufferB = 0; ///< Bufor pomocniczy na ewentualny drugi surowiec (np. dla hut).
    public:
        virtual ~Factory() = default;

        /**
         * @brief Renderuje obiekt fabryki w przestrzeni symulacyjnej.
         * @param window Referencja do okna SFML.
         */
        void draw(sf::RenderWindow& window) override;

        /**
         * @brief Główna pętla fabryki.
         * * Posiada wbudowaną obsługę wyjątków (try-catch dla EmptyStorageException),
         * dzięki czemu bezpiecznie pauzuje produkcję w wypadku przerw w dostawach.
         */
        void update() override;

        /**
         * @brief Przetwarza surowce z buforów wejściowych na wynikową produkcję.
         * @throw EmptyStorageException Zgłaszany automatycznie, gdy w buforze brakuje materiału.
         */
        virtual void processResources() = 0;

        /**
         * @brief Dodaje określoną ilość głównego surowca do bufora wejściowego A.
         * @param amount Ilość surowca do dodania (wartości ujemne są ignorowane przez system walidacji).
         */
        void addInputA(int amount);

        /**
         * @brief Dodaje określoną ilość dodatkowego surowca do bufora wejściowego B.
         * @param amount Ilość surowca do dodania (wartości ujemne są ignorowane).
         */
        void addInputB(int amount);

        /**
         * @brief Pobiera zdefiniowaną ilość surowca z bufora A na potrzeby produkcji.
         * @param amount Ilość surowca do spalenia/przetworzenia.
         * @throw EmptyStorageException Rzucany natychmiast, gdy bufor posiada mniej surowca niż żądana wartość.
         */
        void consumeInputA(int amount);

        /**
         * @brief Pobiera zdefiniowaną ilość surowca z bufora B na potrzeby produkcji.
         * @param amount Ilość surowca do spalenia/przetworzenia.
         * @throw EmptyStorageException Rzucany natychmiast, gdy bufor posiada mniej surowca niż żądana wartość.
         */
        void consumeInputB(int amount);

        // Gettery
        /**
         * @brief Zwraca aktualny stan głównego magazynu wejściowego.
         * @return Liczba jednostek surowca dostępna w buforze A.
         */
        int getInputBufferA() const { return inputBufferA; }

        /**
         * @brief Zwraca aktualny stan pomocniczego magazynu wejściowego.
         * @return Liczba jednostek surowca dostępna w buforze B.
         */
        int getInputBufferB() const { return inputBufferB; }
    };

}