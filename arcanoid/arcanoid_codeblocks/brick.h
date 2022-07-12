#pragma once

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "object.h"
#include "forms.h"
#include "properties.h"

namespace Arcanoid {
    class Brick : public Object, public RectangleForm, public Destroyable {

        public:
            explicit Brick(const int start_x, const int start_y):
                     RectangleForm(start_x, start_y, BRICK_WIDTH, BRICK_HEIGHT, sf::Color::Yellow) {}
    };
}