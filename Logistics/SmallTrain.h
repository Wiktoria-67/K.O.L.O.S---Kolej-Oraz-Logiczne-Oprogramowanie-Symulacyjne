#pragma once
#include "Train.h" // Inkludujemy plik z tego samego folderu

namespace Logistics {

    // Kompilator wie, że Train jest wewnątrz namespace Logistics
    class SmallTrain : public Train { 
    public:
        SmallTrain();
    };

}