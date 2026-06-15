cmake_minimum_required(VERSION 3.14)
cmake_policy(SET CMP0135 NEW)

project(KOLOS_Simulation CXX)

# Standard C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Graphics Window System REQUIRED)

set(LIBRARY_SOURCES
    
    # Moduł Core
    Core/SimulationEngine.cpp
    Core/Renderer.cpp
    Core/Button.cpp
    Core/InfoPanel.cpp
    Core/SimulationEngine.h
    Core/Renderer.h
    Core/Button.h
    Core/InfoPanel.h
    Core/IClickable.h
    Core/IDrawable.h
    Core/MapObject.h
    Core/RenderException.h
    Core/SharedTypes.h
    Core/UIElement.h
    Core/application.h
    Core/application.cpp




    
    # Moduł Logistics
    Logistics/Train.cpp
    Logistics/SmallTrain.cpp
    Logistics/MediumTrain.cpp
    Logistics/LargeTrain.cpp
    Logistics/TrackNetwork.cpp
    Logistics/Train.h
    Logistics/SmallTrain.h
    Logistics/MediumTrain.h
    Logistics/LargeTrain.h
    Logistics/TrackNetwork.h
    Logistics/CapacityExceededException.h
    Logistics/CollisionException.h
    Logistics/Route.h
    
    # Moduł Industry
    Industry/Factory.cpp
    Industry/PowerPlant.cpp
    Industry/SteelMill.cpp
    Industry/MachineFactory.cpp
    Industry/Mine.cpp
    Industry/CoalMine.cpp
    Industry/IronMine.cpp
    Industry/EmptyStorageException.cpp
    Industry/Factory.h
    Industry/PowerPlant.h
    Industry/SteelMill.h
    Industry/MachineFactory.h
    Industry/Mine.h
    Industry/CoalMine.h
    Industry/IronMine.h
    Industry/EmptyStorageException.h
)

add_library(KOLOS_Lib STATIC ${LIBRARY_SOURCES})

target_include_directories(KOLOS_Lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Łączymy projekt z modułami SFML (Graphics, Window, System)
#target_link_libraries(KOLOS PRIVATE sfml-graphics sfml-window sfml-system)
target_link_libraries(KOLOS_Lib PUBLIC SFML::Graphics SFML::Window SFML::System)

add_executable(KOLOS main.cpp)
target_link_libraries(KOLOS PRIVATE KOLOS_Lib)


# Kopiowanie folderu z zasobami (assets) z repozytorium do folderu build
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

# ŚRODOWISKO TESTOWE (Google Test)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)

FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(KOLOS_Tests tests/Tests.cpp)

target_link_libraries(KOLOS_Tests PRIVATE KOLOS_Lib GTest::gtest_main)

include(GoogleTest)
#gtest_discover_tests(KOLOS_Tests)
add_test(NAME AllTests COMMAND KOLOS_Tests)