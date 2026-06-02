#include "Factory.h"
#include "EmptyStorageException.h"

namespace Industry {

    void Factory::draw() {
        // Docelowo: Rysowanie budynku fabryki na mapie
    }

    void Factory::update() {
        // W każdym ticku symulacji fabryka próbuje produkować
        try {
            processResources();
        } 
        catch (const EmptyStorageException& e) {
            // Wyłapujemy błąd braku surowców.
            // Tutaj można np. zmienić stan animacji fabryki na "stoi w miejscu"
            // lub wyrysować czerwoną ikonkę braku zasobów.
        }
    }

} // namespace Industry