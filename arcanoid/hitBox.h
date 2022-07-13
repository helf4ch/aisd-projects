#pragma once

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "object.h"
#include "forms.h"
#include "properties.h"

namespace Arcanoid {
    class HitBox : public Object, public RectangleForm {

        public:
            explicit HitBox(const int start_x, const int start_y, const int width, const int height, 
                            const sf::Color color = sf::Color::Transparent):
                     RectangleForm(start_x, start_y, width, height, color) {}
    };
}