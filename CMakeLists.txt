cmake_minimum_required(VERSION 3.10)

# Nazwa Waszego projektu i używany język
project(KOLOS_Simulation CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
find_package(SFML COMPONENTS Graphics Window System REQUIRED)
include_directories("/opt/homebrew/include")
# Dodajemy wszystkie pliki źródłowe (.cpp) do kompilacji
set(SOURCES
    main.cpp
    
    # Moduł Core
    Core/SimulationEngine.cpp
    Core/Renderer.cpp
    Core/Button.cpp
    Core/InfoPanel.cpp
    
    # Moduł Logistics
    Logistics/Train.cpp
    Logistics/SmallTrain.cpp
    Logistics/MediumTrain.cpp
    Logistics/LargeTrain.cpp
    Logistics/TrackNetwork.cpp
    
    # Moduł Industry
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
target_link_libraries(KOLOS PRIVATE SFML::Graphics SFML::Window SFML::System)

# Wskazujemy folder główny jako bazę do include'ów
target_include_directories(KOLOS PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
