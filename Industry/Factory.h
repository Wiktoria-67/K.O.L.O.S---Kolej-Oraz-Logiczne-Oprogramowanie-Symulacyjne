#pragma once
#include "../Core/MapObject.h"

namespace Industry {

/**
     * @class Factory
     * @brief Abstrakcyjna klasa bazowa dla wszystkich fabryk w grze.
     * * Zarządza buforami wejściowymi na surowce i buforem wyjściowym na gotowe produkty.
     */
    class Factory : public Core::MapObject {
    private:
        int inputBufferA = 0;  ///< Bufor na pierwszy wymagany surowiec (np. węgiel).
        int inputBufferB = 0;  ///< Bufor na drugi wymagany surowiec (np. rudę).

    protected:
        int outputBuffer = 0; ///< Bufor na wyprodukowane dobra (np. stal).

    public:
        virtual ~Factory() = default;
        
        void draw(sf::RenderWindow& window) override;
        void update() override;

        /**
         * @brief Czysto wirtualna metoda definiująca specyficzny proces produkcji danej fabryki.
         */
        virtual void processResources() = 0;
        
        /**
         * @brief Dodaje surowce do pierwszego bufora wejściowego.
         * @param amount Ilość surowca do dodania.
         */
        void addInputA(int amount);

        /**
         * @brief Dodaje surowce do drugiego bufora wejściowego.
         * @param amount Ilość surowca do dodania.
         */
        void addInputB(int amount);

        /**
         * @brief Pobiera (zużywa) surowce z pierwszego bufora wejściowego.
         * @param amount Ilość surowca do zużycia.
         */
        void consumeInputA(int amount);

        /**
         * @brief Pobiera (zużywa) surowce z drugiego bufora wejściowego.
         * @param amount Ilość surowca do zużycia.
         */
        void consumeInputB(int amount);
        
        /**
         * @brief Zwraca aktualny stan pierwszego bufora wejściowego.
         * @return Ilość surowca w buforze A.
         */
        int getInputBufferA() const { return inputBufferA; }

        /**
         * @brief Zwraca aktualny stan drugiego bufora wejściowego.
         * @return Ilość surowca w buforze B.
         */
        int getInputBufferB() const { return inputBufferB; }

        /**
         * @brief Zwraca ilość gotowych produktów w magazynie wyjściowym.
         * @return Ilość gotowych dóbr przygotowanych do odbioru.
         */
        int getOutputBuffer() const { return outputBuffer; }

        /**
         * @brief Zwiększa stan bufora wyjściowego o podaną wartość.
         * @param amount Ilość wyprodukowanego towaru do dodania.
         */
        void increaseOutputBuffer(int amount) { if(amount > 0) outputBuffer += amount; }

        /**
         * @brief Zmniejsza stan bufora wyjściowego (np. podczas załadunku na pociąg).
         * @param amount Ilość pobieranego towaru przez jednostkę transportową.
         */
        void decreaseOutputBuffer(int amount) { if(outputBuffer >= amount) outputBuffer -= amount; }
    };
}