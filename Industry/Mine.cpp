#include "Mine.h"

namespace Industry {

    void Mine::draw() {
        // Docelowo: Wywolanie funkcji z biblioteki graficznej (np. rysowanie sprite'a)
    }

    void Mine::update() {
        // Główna pętla odliczająca czas do wykopania surowca
        if (resourceTimer > 0) {
            resourceTimer--;
        } else {
            generateResource(); // Wywołanie polimorficzne
            resourceTimer = 100; // Reset timera po wydobyciu (przykładowa wartość)
        }
    }

} // namespace Industry