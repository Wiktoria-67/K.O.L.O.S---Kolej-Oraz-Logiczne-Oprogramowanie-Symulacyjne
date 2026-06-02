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
    Core/SimulationEngine.cpp
    Core/Renderer.cpp
    Core/Button.cpp
    Core/InfoPanel.cpp
    # Tu dodacie kolejne pliki cpp w miarę postępu prac
)

# Tworzymy plik wykonywalny
add_executable(KOLOS ${SOURCES})