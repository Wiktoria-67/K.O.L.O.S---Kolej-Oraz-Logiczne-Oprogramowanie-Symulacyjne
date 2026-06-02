cmake_minimum_required(VERSION 3.10)

# Nazwa Waszego projektu i używany język
project(KOLOS_Simulation CXX)

# Wymuszamy standard C++20 zgodnie z dokumentacją
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Dodajemy wszystkie pliki źródłowe (.cpp) do kompilacji
# (Na razie wpisujemy te, które stworzymy w pierwszym kroku)
set(SOURCES
    main.cpp
    
    # Moduł Core (Programista 1)
    Core/SimulationEngine.cpp
    Core/Renderer.cpp
    Core/Button.cpp
    Core/InfoPanel.cpp
    
    # Moduł Logistics (Programista 2)
    Logistics/Train.cpp
    Logistics/SmallTrain.cpp
    Logistics/MediumTrain.cpp
    Logistics/LargeTrain.cpp
    Logistics/TrackNetwork.cpp
    
    # Moduł Industry (Programista 3)
    Industry/Factory.cpp
    Industry/PowerPlant.cpp
    Industry/SteelMill.cpp
    Industry/MachineFactory.cpp
    Industry/Mine.cpp
    Industry/CoalMine.cpp
    Industry/IronMine.cpp
    Industry/EmptyStorageException.cpp
)

# Tworzymy plik wykonywalny
add_executable(KOLOS ${SOURCES})