#pragma once
#include <SFML/Graphics.hpp>
#include "IDrawable.h"
#include "IClickable.h"
#include "SharedTypes.h"

namespace Core {

    /**
     * @class UIElement
     * @brief Abstrakcyjna klasa bazowa dla elementów interfejsu użytkownika (GUI).
     * * Łączy w sobie cechy obiektów rysowalnych oraz klikalnych.
     */
    class UIElement : public IDrawable, public IClickable {
    protected:
        Point2D position; ///< Lewy górny róg elementu UI.
        int width; ///< Szerokość elementu w pikselach.
        int height; ///< Wysokość elementu w pikselach.
    public:
        virtual ~UIElement() = default;
        void draw(sf::RenderWindow& window) override = 0;
        bool onClick(int mouseX, int mouseY) override = 0;
    };
}