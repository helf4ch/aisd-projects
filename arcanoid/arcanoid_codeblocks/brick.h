#pragma once

#include <SFML/Graphics.hpp>

#include "constants.h"
#include "object.h"
#include "forms.h"
#include "properties.h"

namespace Arcanoid {
    class Brick : public Object, public RectangleForm, public Destroyable {

        public:
            explicit Brick(const int start_x, const int start_y, const sf::Color color = sf::Color::Yellow):
                     RectangleForm(start_x, start_y, BRICK_WIDTH, BRICK_HEIGHT, color) {}
    };
}